# $NetBSD: buildlink3.mk,v 1.3 2014/05/16 20:47:11 szptvlfn Exp $

BUILDLINK_TREE+=	hs-json

.if !defined(HS_JSON_BUILDLINK3_MK)
HS_JSON_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-json+=	hs-json>=0.7
BUILDLINK_PKGSRCDIR.hs-json?=	../../wip/hs-json

.include "../../devel/hs-mtl/buildlink3.mk"
.include "../../wip/hs-text/buildlink3.mk"
.endif	# HS_JSON_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-json
