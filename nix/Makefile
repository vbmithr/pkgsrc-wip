# $NetBSD$

DISTNAME=		nix-2.3.1
CATEGORIES=		wip
MASTER_SITES=		${MASTER_SITE_GITHUB:=NixOS/}

MAINTAINER=		ng0@NetBSD.org
HOMEPAGE=		https://github.com/NixOS/nix/
COMMENT=		Purely functional package manager
LICENSE=		gnu-lgpl-v2.1

USE_TOOLS+=		pkg-config flex bash bison gmake
USE_TOOLS+=		automake autoconf autoreconf
USE_LANGUAGES=		c c++
GNU_CONFIGURE=		YES

BUILD_DEPENDS+=		autoconf-archive-[0-9]*:../../devel/autoconf-archive

PKGCONFIG_OVERRIDE+=	src/libexpr/nix-expr.pc.in
PKGCONFIG_OVERRIDE+=	src/libmain/nix-main.pc.in
PKGCONFIG_OVERRIDE+=	src/libstore/nix-store.pc.in

.include "../../mk/bsd.prefs.mk"

CONFIGURE_ARGS+=	--with-sandbox-shell=/bin/sh
CONFIGURE_ARGS+=	--enable-gc

# s3 option needs s3-cpp, this was reported as a cause for error if
# left unchanged.
CONFIGURE_ENV+=		ac_cv_header_aws_s3_S3Client_h=no
#CONFIGURE_ENV+=	EDITLINE_CFLAGS=${BUILDLINK_PREFIX.editlinereadline:Q}/include
#CONFIGURE_ENV+=	EDITLINE_LIBS=${BUILDLINK_PREFIX.editlinereadline:Q}/lib
#CONFIGURE_ENV+=	EDITLINE_CFLAGS=${BUILDLINK_PREFIX.editlinereadline:Q}/include/readline
CONFIGURE_ENV+=		EDITLINE_CFLAGS="-DREADLINE"
CONFIGURE_ENV+=		EDITLINE_LIBS=${BUILDLINK_PREFIX.editlinereadline:Q}/lib
#CONFIGURE_ENV+=	EDITLINE_CFLAGS=${BUILDLINK_PREFIX.editline:Q}/include/readline
#CONFIGURE_ENV+=	EDITLINE_LIBS=${BUILDLINK_PREFIX.editline:Q}/lib
CONFIGURE_ENV+=		LIBLZMA_CFLAGS=${BUILDLINK_PREFIX.lzmalib:Q}/include
CONFIGURE_ENV+=		LIBLZMA_LIBS=${BUILDLINK_PREFIX.lzmalib:Q}/lib
CONFIGURE_ENV+=		BOOST_ROOT=${BUILDLINK_PREFIX.boost:Q}/lib

# Workaround for:
#   /usr/bin/ld: error: undefined symbol: SHA512_Update
MAKE_ARGS+=	libutil_ALLOW_UNDEFINED=yes

# verbose build
# MAKE_ENV+=	V=1
# Disable hardcoded -O3
# MAKE_ENV+=	OPTIMIZE=0

# checking for aws/s3/S3Client.h... (cached) no
# ./configure: 7863: Syntax error: "(" unexpected (expecting "fi")
# *** Error code 2
# hack configure.ac bashism, work on an upstream fix for this,
# thanks 0mp@FreeBSD.org for this tiny detail:
CONFIG_SHELL=		${TOOLS_PATH.bash}

# incomplete, remove once the docs build
CONFIGURE_ARGS+=	--disable-doc-gen

SUBST_CLASSES+=		docbook
SUBST_MESSAGE.docbook=	Fixing docbook URLs.
SUBST_FILES.docbook+=	doc/manual/installation/prerequisites-source.xml
SUBST_FILES.docbook+=	doc/manual/local.mk
SUBST_FILES.docbook+=	doc/manual/manual.xmli
SUBST_STAGE.docbook=	pre-configure
SUBST_SED.docbook+=	-e 's,http://docbook.sourceforge.net/release/xsl/current,${PREFIX}/share/xsl/docbook,g'

# and one more.
SUBST_CLASSES+=		docbook2
SUBST_MESSAGE.docbook2=	Fixing docbook URLs.
SUBST_FILES.docbook2+=	doc/manual/local.mk
SUBST_STAGE.docbook2=	pre-configure
SUBST_SED.docbook2+=	-e 's,http://docbook.org/xml/5.0/rng/docbook.rng,${PREFIX}/share/xsl/docbook,g'

BUILD_DEPENDS+=	libxslt-[0-9]*:../../textproc/libxslt
BUILD_DEPENDS+=	docbook-xsl-[0-9]*:../../textproc/docbook-xsl

#.if ${OPSYS} == "NetBSD"
#USE_BUILTIN.editline=	yes
#READLINE_DEFAULT=	readline
#.endif

#.include "../../mk/readline.buildlink3.mk"
# .if ${READLINE_TYPE} == "readline"
# SUBST_CLASSES+=		editline
# SUBST_MESSAGE.editline=	Fixing editline header.
# SUBST_STAGE.editline=	pre-configure
# SUBST_FILES.editline=	src/nix/repl.cc
# SUBST_SED.editline=	-e "s,editline\.h,readline\.h,g"
# .endif

pre-configure:
	cd ${WRKSRC} && ${SH} bootstrap.sh

.include "../../archivers/lzmalib/buildlink3.mk"
.include "../../archivers/brotli/buildlink3.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
.include "../../devel/boehm-gc/buildlink3.mk"
.include "../../devel/editline/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../security/libsodium/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
