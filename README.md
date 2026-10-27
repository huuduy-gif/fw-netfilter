# fw-netfilter

Tuong lua bang Netfilter Kernel Module (mon He quan tri mang Linux).

## Build
    make            # build module
    sudo insmod fw_netfilter.ko
    sudo rmmod fw_netfilter

## Quy uoc
- `main` luon build va nap duoc. Khong push thang vao main.
- Nhanh: `feat/<ten>-<viec>` (vd: feat/b-hooks), gop qua Pull Request, A review.
- Kernel code theo chuan Linux (tab 8). Moi log co tien to `fw:`.
- Header chung: `include/fw_common.h` (A giu, muon doi phai bao A).
