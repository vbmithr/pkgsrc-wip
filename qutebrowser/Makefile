# $NetBSD$

DISTNAME=	qutebrowser-1.10.1
CATEGORIES=	www
MASTER_SITES=	${MASTER_SITE_GITHUB:=qutebrowser/}
GITHUB_TAG=	v1.10.1

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://qutebrowser.org/
COMMENT=	Keyboard-driven, vim-like browser based on PyQt5
LICENSE=	gnu-gpl-v3

USE_LANGUAGES=	# none

DEPENDS+=	${PYPKGPREFIX}-PEG2-[0-9]*:../../wip/py-PEG2
DEPENDS+=	${PYPKGPREFIX}-attrs-[0-9]*:../../devel/py-attrs
DEPENDS+=	${PYPKGPREFIX}-cssutils-[0-9]*:../../textproc/py-cssutils
DEPENDS+=	${PYPKGPREFIX}-jinja2-[0-9]*:../../textproc/py-jinja2
DEPENDS+=	${PYPKGPREFIX}-pygments-[0-9]*:../../textproc/py-pygments
DEPENDS+=	${PYPKGPREFIX}-yaml-[0-9]*:../../textproc/py-yaml

TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools-[0-9]*:../../devel/py-setuptools
TOOL_DEPENDS+=	asciidoc-[0-9]*:../../textproc/asciidoc

PYTHON_VERSIONS_INCOMPATIBLE=	27

.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../lang/python/egg.mk"
.include "../../x11/py-qt5/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
