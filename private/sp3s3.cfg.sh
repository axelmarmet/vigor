
# Config for 10G:
# [mb]{p801p1 (90:e2:ba:55:12:5c)} -- {p801p1 ()}[server]
# [mb]{p802p2 (90:e2:ba:55:14:11)/dev6} -- {p802p2 (90:e2:ba:55:12:25)/dev8}[tester]
# [mb]{p802p1 (90:e2:ba:55:14:10)/dev5} -- {p802p1 (90:e2:ba:55:12:24)/dev7}[tester]

# direct link tester:
# p802p2 90:e2:ba:55:12:25 -- p801p1 90:e2:ba:55:14:38

KERN_NIC_DRIVER=ixgbe
DPDK_NIC_DRIVER=igb_uio

# Subnets

EXTERNAL_SUBNET=192.168.4.0
SERVER_SUBNET=192.168.150.0

# Middlebox

MB_HOST=icnalsp3s3.epfl.ch


MB_MAC_INTERNAL=90:e2:ba:55:13:e4
MB_MAC_EXTERNAL=90:e2:ba:55:13:e5
# MB_MAC_TO_SRV=90:e2:ba:55:12:5c

MB_IP_INTERNAL=192.168.6.2
MB_IP_EXTERNAL=192.168.4.2
# MB_IP_TO_SRV=192.168.150.2

MB_DEVICE_INTERNAL=ens4
MB_DEVICE_EXTERNAL=ens5
# MB_DEVICE_TO_SRV=p801p1

MB_PCI_INTERNAL=0000:00:04.0
MB_PCI_EXTERNAL=0000:00:05.0
# MB_PCI_TO_SRV=0000:85:00.0


# Tester

TESTER_HOST=matteo@icnalsp3s1.epfl.ch

TESTER_DEVICE_INTERNAL=p787p1
TESTER_DEVICE_EXTERNAL=p787p2

TESTER_PCI_INTERNAL=0000:81:00.0
TESTER_PCI_EXTERNAL=0000:81:00.1

TESTER_MAC_INTERNAL=90:e2:ba:55:14:24
TESTER_MAC_EXTERNAL=90:e2:ba:55:14:25

TESTER_IP_INTERNAL=192.168.6.5
TESTER_IP_EXTERNAL=192.168.4.10
TESTER_IP_FOR_STUB=192.168.150.5

# Server

SERVER_HOST=icnalsp3s3.epfl.ch

SERVER_IP=192.168.150.10
SERVER_MAC=90:e2:ba:55:14:54
SERVER_DEVICE=p801p1

# Other

CASE_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}")"/../../../../  >/dev/null && pwd )"

# Fix the case root folder for the tester, where it should be just home
if [ "${CASE_ROOT##/home/}" == "${CASE_ROOT}" ]; then
  CASE_ROOT=$HOME
fi

export RTE_SDK=$CASE_ROOT/dpdk
export RTE_TARGET=x86_64-native-linuxapp-gcc