TEMPLATE = app
TARGET = testDHT
INCLUDEPATH += .

# Input
HEADERS += common_dht_read.h pi_2_dht_read.h pi_2_mmio.h test_dht_read.h
SOURCES += common_dht_read.c pi_2_dht_read.c pi_2_mmio.c test_dht_read.c

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
