# $NetBSD$

DISTNAME=	gh-0.5.5
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=cli/}
GITHUB_PROJECT=	cli
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://cli.github.com/
COMMENT=	GitHub CLI
LICENSE=	mit

GO_DIST_BASE=	${DISTNAME:S/gh/cli/}
GO_SRCPATH=	github.com/cli/cli

DEPENDS+=		git-base-[0-9]*:../../devel/git-base

GO_DEPS+=	github.com/AlecAivazis/survey:eb3a4d3114c3ec1cc6fd0b0d28afac0208a37fac
GO_DEPS+=	github.com/alecthomas/chroma:330c3bd39c1404bf1974a8e2fb27c1e57f54440b
GO_DEPS+=	github.com/aybabtme/rgbterm:cc83f3b3ce5911279513a46d6d3316d67bedaa54
GO_DEPS+=	github.com/cpuguy83/go-md2man:217d7bd9dd5494abdf2877afbeb24ba0e11b43d6
#GO_DEPS+=	github.com/go-yaml/yaml:53403b58ad1b561927d19068c655246f2db79d48:gopkg.in/yaml.v2
GO_DEPS+=	github.com/go-yaml/yaml:a6ecf24a6d716d933bcbc255a2f5d492285b54f5:gopkg.in/yaml.v3
GO_DEPS+=	github.com/google/shlex:e7afc7fbc51079733e9468cdfd1efcd7d196cd1d
GO_DEPS+=	github.com/hashicorp/go-version:2b13044f5cdd3833370d41ce57d8bf3cec5e62b8
GO_DEPS+=	github.com/kballard/go-shellquote:95032a82bc518f77982ea72343cc1ade730072f0
GO_DEPS+=	github.com/kr/text:702c74938df48b97370179f33ce2107bd7ff3b3e
GO_DEPS+=	github.com/mattn/go-colorable:c742d6fb21c22a5bb6f768a683e6782e52fe0311
GO_DEPS+=	github.com/mattn/go-isatty:cb30d6282491c185f77d9bec5d25de1bb61a06bc
GO_DEPS+=	github.com/mgutz/ansi:9520e82c474b0a04dd04f8a40959027271bab992
GO_DEPS+=	github.com/mitchellh/go-homedir:af06845cf3004701891bf4fdb884bfe4920b3727
GO_DEPS+=	github.com/mitchellh/go-wordwrap:9e67c67572bc5dd02aef930e2b0ae3c02a4b5a5c
GO_DEPS+=	github.com/russross/blackfriday:3e56bb68c8876389c631e9e318ce3c092a0906db
GO_DEPS+=	github.com/spf13/cobra:89c7ffb5129bebd58cd68878c13af2144a5791f3
GO_DEPS+=	github.com/spf13/pflag:2e9d26c8c37aae03e3f9d4e90b7116f5accb7cab
GO_DEPS+=	github.com/tj/go-css:220a796d1705937ea01e508d9e0e77ef5a4de90c
GO_DEPS+=	github.com/vilmibm/go-termd:ceed4642a3749eee623ccd07457f8d2b82b8fdd2

CHECK_RELRO_SKIP+=	bin/gh

INSTALLATION_DIRS+=	bin

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/bin/gh ${DESTDIR}${PREFIX}/bin

.include "../../lang/go/go-package.mk"
.include "../../security/go-crypto/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
