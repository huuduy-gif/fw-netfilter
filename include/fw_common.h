/* fw_common.h - "hop dong" chung giua kernel module va fwctl.
 * Chi A duoc sua. Muon doi thi bao A va gop qua Pull Request.
 */
#ifndef FW_COMMON_H
#define FW_COMMON_H

#include <linux/types.h>

#define FW_GENL_NAME     "fw_netfilter"
#define FW_GENL_VERSION  1
#define FW_MAX_RULES     1024

/* Hook ap dung (bitmask, mot luat co the gan nhieu hook) */
#define FW_HOOK_PRE_ROUTING   (1 << 0)
#define FW_HOOK_LOCAL_IN      (1 << 1)
#define FW_HOOK_FORWARD       (1 << 2)
#define FW_HOOK_LOCAL_OUT     (1 << 3)
#define FW_HOOK_POST_ROUTING  (1 << 4)
#define FW_HOOK_ALL           0x1F

/* Hanh dong */
enum fw_action {
	FW_ACCEPT = 0,
	FW_DROP   = 1,
};

/* Mot luat. Dia chi IP o dang network byte order,
 * cong o dang host byte order.
 * proto = 0 la moi giao thuc (con lai dung IPPROTO_TCP/UDP/ICMP).
 * Mac dinh "moi IP" = ip 0 mask 0; "moi cong" = min 0, max 65535.
 * Kich thuoc co dinh 48 byte, khong can packed.
 */
struct fw_rule {
	__u32 id;           /* kernel cap khi ADD */
	__u32 src_ip;
	__u32 src_mask;
	__u32 dst_ip;
	__u32 dst_mask;
	__u16 sport_min;
	__u16 sport_max;
	__u16 dport_min;
	__u16 dport_max;
	__u8  proto;
	__u8  hooks;        /* bitmask FW_HOOK_* */
	__u8  action;       /* enum fw_action */
	__u8  pad;
	__u64 pkts;         /* kernel dien khi LIST */
	__u64 bytes;
};

/* Thong ke tong (GET_STATS) */
struct fw_stats {
	__u64 total_pkts;
	__u64 dropped_pkts;
	__u32 active_conns;  /* D (stateful) cap nhat */
	__u32 pad;
};

/* Lenh Generic Netlink */
enum fw_cmd {
	FW_CMD_UNSPEC = 0,
	FW_CMD_ADD,          /* kem FW_ATTR_RULE */
	FW_CMD_DEL,          /* kem FW_ATTR_ID */
	FW_CMD_LIST,         /* tra ve nhieu FW_ATTR_RULE */
	FW_CMD_FLUSH,        /* xoa het luat */
	FW_CMD_SET_POLICY,   /* kem FW_ATTR_POLICY */
	FW_CMD_GET_STATS,    /* tra ve FW_ATTR_STATS */
	__FW_CMD_MAX,
};
#define FW_CMD_MAX (__FW_CMD_MAX - 1)

/* Thuoc tinh Netlink */
enum fw_attr {
	FW_ATTR_UNSPEC = 0,
	FW_ATTR_RULE,        /* binary: struct fw_rule */
	FW_ATTR_ID,          /* u32 */
	FW_ATTR_POLICY,      /* u8: enum fw_action */
	FW_ATTR_STATS,       /* binary: struct fw_stats */
	__FW_ATTR_MAX,
};
#define FW_ATTR_MAX (__FW_ATTR_MAX - 1)

#endif /* FW_COMMON_H */
