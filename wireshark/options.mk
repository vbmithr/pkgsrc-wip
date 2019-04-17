# $NetBSD: options.mk,v 1.22 2018/12/03 15:35:15 adam Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.wireshark
PKG_SUPPORTED_OPTIONS=		http2 lua qt5
PKG_SUGGESTED_OPTIONS=		qt5 lua

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		icons lua mans qt

.if !empty(PKG_OPTIONS:Mqt5)
.  include "../../x11/qt5-qtsvg/buildlink3.mk"
.  include "../../x11/qt5-qttools/buildlink3.mk"
.  if ${OPSYS} == "Darwin"
.    include "../../x11/qt5-qtmacextras/buildlink3.mk"
.  else
.    include "../../x11/qt5-qtx11extras/buildlink3.mk"
.  endif
PLIST.qt=		yes
.endif

.if empty(PKG_OPTIONS:Mqt5)
#CONFIGURE_ARGS+=	--disable-wireshark
.else
#CONFIGURE_ARGS+=	--enable-wireshark
PLIST.mans=		yes
INSTALLATION_DIRS+=	share/applications
PLIST.icons=		yes
POST_INSTALL_TARGETS+=	install-icons
INSTALLATION_DIRS+=	share/icons/hicolor/scalable/apps
ICON_SIZES=		16 32 48
MIMEICON_SIZES=		16 24 32 48 64 128 256

.  for d in ${ICON_SIZES}
INSTALLATION_DIRS+=	share/icons/hicolor/${d}x${d}/apps
.  endfor

.  for d in ${MIMEICON_SIZES}
INSTALLATION_DIRS+=	share/icons/hicolor/${d}x${d}/mimetypes
.  endfor

.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"

.PHONY: install-icons
install-icons:
	${INSTALL_DATA} ${WRKSRC}/image/wsicon.svg \
		${DESTDIR}${PREFIX}/share/icons/hicolor/scalable/apps/wireshark.svg
.  for d in ${MIMEICON_SIZES}
	${INSTALL_DATA} ${WRKSRC}/image/WiresharkDoc-${d}.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/${d}x${d}/mimetypes/application-vnd.tcpdump.pcap.png
.  endfor
.endif

.if !empty(PKG_OPTIONS:Mlua)
LUA_VERSIONS_INCOMPATIBLE=	53
.include "../../lang/lua/buildlink3.mk"
#CONFIGURE_ARGS+=	--with-lua=yes
PLIST.lua=		yes
.else
#CONFIGURE_ARGS+=	--with-lua=no
.endif

.if !empty(PKG_OPTIONS:Mhttp2)
.include "../../www/nghttp2/buildlink3.mk"
.endif