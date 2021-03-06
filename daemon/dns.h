#ifndef PETTYCOIN_DNS_H
#define PETTYCOIN_DNS_H
#include "config.h"
#include <ccan/io/io.h>
#include <ccan/tal/tal.h>
#include <ccan/typesafe_cb/typesafe_cb.h>
#include <stdbool.h>

struct lightningd_state;
struct netaddr;

#define dns_resolve_and_connect(dstate, name, port, initfn, failfn, arg) \
	dns_resolve_and_connect_((dstate), (name), (port),		\
			typesafe_cb_preargs(struct io_plan *, void *, \
					    (initfn), (arg),		\
					    struct io_conn *,		\
					    struct lightningd_state *), \
			typesafe_cb_preargs(void, void *, (failfn), (arg), \
					    struct lightningd_state *), \
				 (arg))

struct dns_async *dns_resolve_and_connect_(struct lightningd_state *dstate,
		  const char *name, const char *port,
		  struct io_plan *(*init)(struct io_conn *,
					  struct lightningd_state *,
					  void *arg),
		  void (*fail)(struct lightningd_state *, void *arg),
		  void *arg);

#endif /* PETTYCOIN_DNS_H */
