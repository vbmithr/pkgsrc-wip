# $NetBSD: Makefile,v 1.17 2019/02/27 14:29:58 gdt Exp $

# Do not merge to pkgsrc without gdt approval; I have not yet
# evaluated how much this will break.
VERSION_BASE=	7.0.0
VERSION_RC=
VERSION=	${VERSION_BASE}${VERSION_RC}
#PKGREVISION=	0
# proj RCs have names like 5.1.0RC1 but unpack to 5.1.0
WRKFINAL=	proj-${VERSION_BASE}
WRKSRC=		${WRKDIR}/${WRKFINAL}
DISTNAME=	proj-${VERSION}
CATEGORIES=	geography
MASTER_SITES=	https://download.osgeo.org/proj/
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	gdt@NetBSD.org
HOMEPAGE=	https://proj4.org/
COMMENT=	Cartographic projection software

# \todo: Add pdf manual.

# \todo Think about how this works with the new grid CDN.
# Grid files also have the following "cc-by ish" licenses:
# cc-by, 2-clause-bsd,  License Ouverte, cc0 (eu)
# open-government, cc-by, public-domain (na)
# cc-by (oceania)
LICENSE=	mit

.include "options.mk"

PREV_PKGPATH=		misc/proj

USE_LANGUAGES=		c99 c++11
USE_LIBTOOL=		yes
USE_TOOLS+=		gmake pkg-config
GNU_CONFIGURE=		yes

# \todo Debug this.
# Tests fail if proj relies on NetBSD 8's C99 math, vs proj's
# replacement functions.
.if ${OPSYS} == "NetBSD"
CFLAGS+=		-DHAVE_C99_MATH=0
.endif

.if !empty(PKG_OPTIONS:Mproj-grids)
# Ideally, upstream would have an approach which enables testing with
# the grids that users ought to have.  Until then, fail if test
# preconditions are not met.
do-test:
	${ECHO} "Tests assume extra grids are not installed."
	${FALSE}
.else
TEST_TARGET=		check
.endif

# \todo Ideally, the files would be unpacked directly in data.
# Assume that all of the stray files in ${WRKDIR} came from datumgrids.
# \todo Some files in the grid tarballs do not get installed by the
# base Makefile.  Consider an alternate approach.
post-extract:
	cd ${WRKDIR} && for f in *; do if [ $$f != ${WRKFINAL} ]; then mv $$f ${WRKFINAL}/data; fi; done

.include "../../databases/sqlite3/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
