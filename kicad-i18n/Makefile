# $NetBSD: Makefile,v 1.3 2018/03/01 13:59:11 mef Exp $
#

V=		5.1.0
DISTNAME=	kicad-i18n-${V}
CATEGORIES=	cad
MASTER_SITES=	${MASTER_SITE_GITHUB:=KiCad/}
GITHUB_TAG=	${PKGVERSION_NOREV}
EXTRACT_SUFX=	.zip


MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://kicad-pcb.org/
COMMENT=	user interface translations for the PCB CAD software
LICENSE=	gnu-gpl-v3
CMAKE_ARGS+=	-DKICAD_REPO_NAME=stable -DKICAD_BUILD_VERSION=${V}

USE_CMAKE=	yes
BUILD_DIRS=	obj
CONFIGURE_DIRS=	${BUILD_DIRS}
CMAKE_ARG_PATH=	..

pre-configure:
	cd ${WRKSRC} && mkdir ${BUILD_DIRS}

.include "../../devel/cmake/buildlink3.mk"
.include "../../mk/bsd.prefs.mk"
.include "../../mk/bsd.pkg.mk"
