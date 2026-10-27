#!/bin/bash
# Dung: bash tests/quick_test.sh [so-PR | ten-nhanh]   (mac dinh: main)
cd "$(dirname "$0")/.." || exit 1
MOD=fw_netfilter
TARGET=${1:-main}

if [[ "$TARGET" =~ ^[0-9]+$ ]]; then
  git fetch origin "pull/$TARGET/head" && git checkout --detach FETCH_HEAD || exit 1
else
  git fetch origin && git checkout "$TARGET" && git pull origin "$TARGET" || exit 1
fi

echo "== Build =="
make clean >/dev/null 2>&1
make 2>&1 | tee /tmp/fw_build.log
[ "${PIPESTATUS[0]}" -eq 0 ] || { echo "FAIL: build loi"; exit 1; }
grep -i "warning" /tmp/fw_build.log | grep -v "compiler differs" && echo ">> CO WARNING, kiem tra lai" || echo ">> Build sach"

echo "== Nap/go 5 lan =="
for i in 1 2 3 4 5; do
  sudo dmesg -C
  sudo insmod $MOD.ko || { echo "FAIL: insmod lan $i"; exit 1; }
  sleep 1
  sudo rmmod $MOD || { echo "FAIL: rmmod lan $i"; exit 1; }
  if sudo dmesg | grep -Ei "BUG:|Oops|Call Trace|general protection"; then
    echo "FAIL: kernel bao loi o lan $i"; exit 1
  fi
done
echo "== dmesg lan cuoi =="; sudo dmesg | tail -5
echo "== PASS: build, nap, go 5 lan khong loi =="
