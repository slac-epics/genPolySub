TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# Build an IOC support library

LIBRARY_IOC += xxxSupport

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord
# install devXxxSoft.dbd into <top>/dbd
DBD += xxxSupport.dbd

# The following are compiled and added to the Support library
xxxSupport_SRCS += xxxRecord.c
xxxSupport_SRCS += devXxxSoft.c

xxxSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

LIBRARY_IOC += genPolySub
DBD += genPolySub.dbd
genPolySub_SRCS += genPolySub.c
genPolySub_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# build an ioc application

PROD_IOC = poly
# poly.dbd will be created and installed
DBD += poly.dbd

# poly.dbd will be made up from these files:
poly_DBD += base.dbd
poly_DBD += xxxSupport.dbd
poly_DBD += dbSubExample.dbd
poly_DBD += polyHello.dbd
poly_DBD += genSubRecord.dbd



poly_DBD += genSubTestRoutine.dbd
poly_DBD += genPolySub.dbd

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
poly_SRCS += poly_registerRecordDeviceDriver.cpp
poly_SRCS_DEFAULT += polyMain.cpp
poly_SRCS_vxWorks += -nil-

# Add locally compiled object code
poly_SRCS += dbSubExample.c
poly_SRCS += polyHello.c
poly_SRCS += genSubTest.c
#poly_SRCS += genPolySub.c

# The following adds support from base/src/vxWorks
poly_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

poly_LIBS += xxxSupport
poly_LIBS += genSub
poly_LIBS += genPolySub

# NOTE: To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file

ifneq ($(SNCSEQ),)
    # This builds sncExample as a component of poly
    poly_SNCFLAGS += +r
    poly_DBD += sncExample.dbd
    poly_SRCS += sncExample.stt
    poly_LIBS += seq pv

    # The following builds sncProgram as a standalone application
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

poly_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

