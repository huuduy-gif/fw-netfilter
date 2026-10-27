## Viec nay lam gi (ma nhiem vu, vd B2)

## Tu kiem truoc khi xin review
- [ ] `make` khong loi, khong warning
- [ ] Da thu `insmod` va `rmmod` tren VM, `dmesg` khong co BUG/Oops
- [ ] Truoc khi doc header goi tin co `pskb_may_pull`
- [ ] Khong cap phat `GFP_KERNEL` hoac ngu (sleep) trong hook; dung `GFP_ATOMIC`
- [ ] Bang luat dung RCU (doc `rcu_read_lock`, sua thay ban moi)
- [ ] Moi `kmalloc` co `kfree` tuong ung khi go module
- [ ] Log co tien to `fw:`, khong in qua nhieu trong hook
- [ ] Neu doi `include/fw_common.h` thi da bao A
