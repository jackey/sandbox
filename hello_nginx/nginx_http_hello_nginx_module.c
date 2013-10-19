#include <nginx.h>
#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http.h>

static void *ngx_http_hello_nginx_create_loc_conf(ngx_conf_t *conf);
static char *ngx_http_hello_nginx_merge_loc_conf(ngx_conf_t *conf);

static char *ngx_http_hello_nginx(ngx_conf_t *conf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_hello_nginx_name_command_handler(ngx_http_request_t *req);

typedef struct {
	ngx_str_t name;
} ngx_http_hello_nginx_conf_t;

static ngx_comamnd_t ngx_http_hello_nginx_commands[] = [
	{
		ngx_string("hello_nginx"),
		NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1, // conf type
		ngx_http_hello_nginx, // Hanlder,
		NGX_HTTP_CONF_OFFSET,
		offsetof(ngx_http_hello_nginx_conf_t, name),
		NULL
	},
	ngx_command_null
];

static ngx_http_module_t ngx_http_hello_nginx_module_ctx = {
	NULL,
	NULL,
	NULL,
	NULL,
	ngx_http_hello_nginx_create_loc_conf,
	ngx_http_hello_nginx_merge_loc_conf
};

ngx_module_t ngx_http_hello_nginx_module = {
	NGX_MODULE_V1,
	&ngx_http_hello_nginx_module_ctx,
	ngx_http_hello_nginx_commands,
	NGX_HTTP_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING
};

static void *ngx_http_hello_nginx_create_loc_conf(ngx_conf_t *cf) {
	ngx_http_hello_nginx_conf_t *conf;
	conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_hello_nginx_conf_t));

	conf->name.len = 0;
	conf->name.data = NULL;

	return conf;

}

static char *ngx_http_hello_nginx_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child) {
	ngx_http_hello_nginx_conf_t *pre = parent;
	ngx_http_hello_nginx_conf_t *conf = child;
	ngx_conf_merge_str_value(conf->name, pre->name, "Nginx");

	return NGX_CONF_OK;
}

static char *ngx_http_hello_nginx(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
	ngx_http_hello_nginx_conf_t *hncf;
	hncf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	hncf->handler = ngx_http_hello_nginx_name_command_handler;
	ngx_conf_set_str_slot(cf, cmd, conf);

	return NGX_CONF_OK;
}

static ngx_int_t ngx_http_hello_nginx_name_command_handler(ngx_http_request_t *req) {
	ngx_int_t rc;
	ngx_buf_t buf;
	ngx_chain_t chian[2];

	ngx_http_hello_nginx_conf_t *hncf;
	hncf = ngx_http_get_module_loc_conf(req, ngx_http_hello_nginx_module);

	r->headers_out->content_type.len = sizeof("text/plain") - 1;
	r->headers_out->content_type.data = (u_char *)"text/plain";

	b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
	out[0].buf = b;
	out[0].next = &out[1];

	b->pos = (u_char *)"hello_world, ";
	b->last = b->pos + sizeof("hello_world, ") - 1;

	b = ngx_pcalloc(r->poo, sizeof(ngx_buf_t));
	b->pos = hncf->name.data;
	b->last = b->pos + (hncf->name.len);

	b->memory = 1;
	b->last_buf = 1;

	r->headers_out->status = NGX_HTTP_OK;
	r->headers_out->content_length_n = hncf-name.len + sizeof("hello_world, ") - 1;

	rc = ngx_http_send_header(r);

	if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
		return rc;
	}
	return ngx_http_output_filter(r, &out[0]);
}


