# $NetBSD: buildlink3.mk,v 1.3 2014/05/16 20:47:10 szptvlfn Exp $

BUILDLINK_TREE+=	hs-haskelldb-hdbc-sqlite3

.if !defined(HS_HASKELLDB_HDBC_SQLITE3_BUILDLINK3_MK)
HS_HASKELLDB_HDBC_SQLITE3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-haskelldb-hdbc-sqlite3+=	hs-haskelldb-hdbc-sqlite3>=0.13
BUILDLINK_PKGSRCDIR.hs-haskelldb-hdbc-sqlite3?=	../../wip/hs-haskelldb-hdbc-sqlite3

.include "../../wip/hs-haskelldb/buildlink3.mk"
.include "../../wip/hs-haskelldb-hdbc/buildlink3.mk"
.include "../../wip/hs-HDBC/buildlink3.mk"
.include "../../wip/hs-HDBC-sqlite3/buildlink3.mk"
.include "../../devel/hs-mtl/buildlink3.mk"
.endif	# HS_HASKELLDB_HDBC_SQLITE3_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-haskelldb-hdbc-sqlite3
