# $NetBSD: buildlink3.mk,v 1.1 2015/04/11 16:12:57 krytarowski Exp $

BUILDLINK_TREE+=	polkit-qt

.if !defined(POLKIT_QT_BUILDLINK3_MK)
POLKIT_QT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.polkit-qt+=	polkit-qt>=0.9.2
BUILDLINK_ABI_DEPENDS.polkit-qt+=	polkit-qt>=0.9.4nb17
BUILDLINK_PKGSRCDIR.polkit-qt?=	../../security/polkit-qt

.include "../../security/policykit/buildlink3.mk"
.include "../../x11/qt4-libs/buildlink3.mk"
.endif	# POLKIT_QT_BUILDLINK3_MK

BUILDLINK_TREE+=	-polkit-qt
