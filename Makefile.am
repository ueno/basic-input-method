libexec_PROGRAMS = basic-input-method

appsdir = $(datadir)/applications
dist_apps_DATA = org.gtk.TestInputMethod.desktop

org.gtk.TestInputMethod.service: org.gtk.TestInputMethod.service.in
	$(AM_V_GEN) sed \
		-e "s|[@]PACKAGE_NAME@|$(PACKAGE_NAME)|g" \
		-e "s|[@]libexecdir@|$(libexecdir)|g" \
		$< > $@

servicedir = $(datadir)/dbus-1/services
service_DATA = org.gtk.TestInputMethod.service

basic_input_method_SOURCES = basic-input-method.c
basic_input_method_CFLAGS = $(DEPS_CFLAGS)
basic_input_method_LDADD = $(DEPS_LIBS)

EXTRA_DIST = org.gtk.TestInputMethod.service.in
CLEANFILES = org.gtk.TestInputMethod.service

-include $(top_srcdir)/git.mk
