# $NetBSD: buildlink3.mk,v 1.2 2009/04/04 22:13:10 thomasklausner Exp $

BUILDLINK_TREE+=	stfl

.if !defined(STFL_BUILDLINK3_MK)
STFL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.stfl+=	stfl>=0.19
BUILDLINK_PKGSRCDIR.stfl?=	../../wip/stfl
BUILDLINK_DEPMETHOD.stfl?=	build
.endif	# STFL_BUILDLINK3_MK

BUILDLINK_TREE+=	-stfl
