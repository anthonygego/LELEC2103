#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Microchip/Common/TimeDelay.c Microchip/MDDFileSystem/FSIO.c Microchip/MDDFileSystem/SD-SPI.c Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c Microchip/TCPIPStack/WIFI/WFConnectionManager.c Microchip/TCPIPStack/WIFI/WFConnectionProfile.c Microchip/TCPIPStack/WIFI/WFDataTxRx.c Microchip/TCPIPStack/WIFI/WFDriverCom.c Microchip/TCPIPStack/WIFI/WFDriverRaw.c Microchip/TCPIPStack/WIFI/WFEventHandler.c Microchip/TCPIPStack/WIFI/WFInit.c Microchip/TCPIPStack/WIFI/WFMac.c Microchip/TCPIPStack/WIFI/WFMgmtMsg.c Microchip/TCPIPStack/WIFI/WFParamMsg.c Microchip/TCPIPStack/WIFI/WFPowerSave.c Microchip/TCPIPStack/WIFI/WFScan.c Microchip/TCPIPStack/WIFI/WFTxPower.c Microchip/TCPIPStack/WIFI/WF_Eint.c Microchip/TCPIPStack/WIFI/WF_Spi.c Microchip/TCPIPStack/WiFi/WF_pbkdf2.c Microchip/TCPIPStack/ARP.c Microchip/TCPIPStack/Announce.c Microchip/TCPIPStack/AutoIP.c Microchip/TCPIPStack/BerkeleyAPI.c Microchip/TCPIPStack/DHCP.c Microchip/TCPIPStack/DHCPs.c Microchip/TCPIPStack/DNS.c Microchip/TCPIPStack/DNSs.c Microchip/TCPIPStack/DynDNS.c Microchip/TCPIPStack/FTP.c Microchip/TCPIPStack/FileSystem.c Microchip/TCPIPStack/HTTP2.c Microchip/TCPIPStack/Hashes.c Microchip/TCPIPStack/Helpers.c Microchip/TCPIPStack/ICMP.c Microchip/TCPIPStack/IP.c Microchip/TCPIPStack/MPFS2.c Microchip/TCPIPStack/NBNS.c Microchip/TCPIPStack/RSA.c Microchip/TCPIPStack/Random.c Microchip/TCPIPStack/Reboot.c Microchip/TCPIPStack/SMTP.c Microchip/TCPIPStack/SNMP.c Microchip/TCPIPStack/SNMPv3.c Microchip/TCPIPStack/SNTP.c Microchip/TCPIPStack/SPIFlash.c Microchip/TCPIPStack/SSL.c Microchip/TCPIPStack/StackTsk.c Microchip/TCPIPStack/TCP.c Microchip/TCPIPStack/TCPPerformanceTest.c Microchip/TCPIPStack/TFTPc.c Microchip/TCPIPStack/Telnet.c Microchip/TCPIPStack/Tick.c Microchip/TCPIPStack/UDP.c Microchip/Transceivers/MRF24J40/MRF24J40.c Microchip/Transceivers/crc.c Microchip/Transceivers/security.c Microchip/WirelessProtocols/P2P/P2P.c Microchip/WirelessProtocols/SymbolTime.c MPack/mpack-common.c MPack/mpack-expect.c MPack/mpack-internal.c MPack/mpack-node.c MPack/mpack-platform.c MPack/mpack-reader.c MPack/mpack-writer.c MyFiles/MyCAN.c MyFiles/MyConsole.c MyFiles/MyFlash.c MyFiles/MyHTTP.c MyFiles/MyIO.c MyFiles/MyLED.c MyFiles/MyMDDFS.c MyFiles/MyMIWI.c MyFiles/MyRTCC.c MyFiles/MySPI.c MyFiles/MyTemperature.c MyFiles/MyWIFI.c MyFiles/MyCyclone.c MyFiles/MyApp.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o ${OBJECTDIR}/Microchip/TCPIPStack/IP.o ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o ${OBJECTDIR}/Microchip/TCPIPStack/Random.o ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o ${OBJECTDIR}/Microchip/Transceivers/crc.o ${OBJECTDIR}/Microchip/Transceivers/security.o ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o ${OBJECTDIR}/MPack/mpack-common.o ${OBJECTDIR}/MPack/mpack-expect.o ${OBJECTDIR}/MPack/mpack-internal.o ${OBJECTDIR}/MPack/mpack-node.o ${OBJECTDIR}/MPack/mpack-platform.o ${OBJECTDIR}/MPack/mpack-reader.o ${OBJECTDIR}/MPack/mpack-writer.o ${OBJECTDIR}/MyFiles/MyCAN.o ${OBJECTDIR}/MyFiles/MyConsole.o ${OBJECTDIR}/MyFiles/MyFlash.o ${OBJECTDIR}/MyFiles/MyHTTP.o ${OBJECTDIR}/MyFiles/MyIO.o ${OBJECTDIR}/MyFiles/MyLED.o ${OBJECTDIR}/MyFiles/MyMDDFS.o ${OBJECTDIR}/MyFiles/MyMIWI.o ${OBJECTDIR}/MyFiles/MyRTCC.o ${OBJECTDIR}/MyFiles/MySPI.o ${OBJECTDIR}/MyFiles/MyTemperature.o ${OBJECTDIR}/MyFiles/MyWIFI.o ${OBJECTDIR}/MyFiles/MyCyclone.o ${OBJECTDIR}/MyFiles/MyApp.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Microchip/Common/TimeDelay.o.d ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d ${OBJECTDIR}/Microchip/Transceivers/crc.o.d ${OBJECTDIR}/Microchip/Transceivers/security.o.d ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d ${OBJECTDIR}/MPack/mpack-common.o.d ${OBJECTDIR}/MPack/mpack-expect.o.d ${OBJECTDIR}/MPack/mpack-internal.o.d ${OBJECTDIR}/MPack/mpack-node.o.d ${OBJECTDIR}/MPack/mpack-platform.o.d ${OBJECTDIR}/MPack/mpack-reader.o.d ${OBJECTDIR}/MPack/mpack-writer.o.d ${OBJECTDIR}/MyFiles/MyCAN.o.d ${OBJECTDIR}/MyFiles/MyConsole.o.d ${OBJECTDIR}/MyFiles/MyFlash.o.d ${OBJECTDIR}/MyFiles/MyHTTP.o.d ${OBJECTDIR}/MyFiles/MyIO.o.d ${OBJECTDIR}/MyFiles/MyLED.o.d ${OBJECTDIR}/MyFiles/MyMDDFS.o.d ${OBJECTDIR}/MyFiles/MyMIWI.o.d ${OBJECTDIR}/MyFiles/MyRTCC.o.d ${OBJECTDIR}/MyFiles/MySPI.o.d ${OBJECTDIR}/MyFiles/MyTemperature.o.d ${OBJECTDIR}/MyFiles/MyWIFI.o.d ${OBJECTDIR}/MyFiles/MyCyclone.o.d ${OBJECTDIR}/MyFiles/MyApp.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o ${OBJECTDIR}/Microchip/TCPIPStack/IP.o ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o ${OBJECTDIR}/Microchip/TCPIPStack/Random.o ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o ${OBJECTDIR}/Microchip/Transceivers/crc.o ${OBJECTDIR}/Microchip/Transceivers/security.o ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o ${OBJECTDIR}/MPack/mpack-common.o ${OBJECTDIR}/MPack/mpack-expect.o ${OBJECTDIR}/MPack/mpack-internal.o ${OBJECTDIR}/MPack/mpack-node.o ${OBJECTDIR}/MPack/mpack-platform.o ${OBJECTDIR}/MPack/mpack-reader.o ${OBJECTDIR}/MPack/mpack-writer.o ${OBJECTDIR}/MyFiles/MyCAN.o ${OBJECTDIR}/MyFiles/MyConsole.o ${OBJECTDIR}/MyFiles/MyFlash.o ${OBJECTDIR}/MyFiles/MyHTTP.o ${OBJECTDIR}/MyFiles/MyIO.o ${OBJECTDIR}/MyFiles/MyLED.o ${OBJECTDIR}/MyFiles/MyMDDFS.o ${OBJECTDIR}/MyFiles/MyMIWI.o ${OBJECTDIR}/MyFiles/MyRTCC.o ${OBJECTDIR}/MyFiles/MySPI.o ${OBJECTDIR}/MyFiles/MyTemperature.o ${OBJECTDIR}/MyFiles/MyWIFI.o ${OBJECTDIR}/MyFiles/MyCyclone.o ${OBJECTDIR}/MyFiles/MyApp.o

# Source Files
SOURCEFILES=Microchip/Common/TimeDelay.c Microchip/MDDFileSystem/FSIO.c Microchip/MDDFileSystem/SD-SPI.c Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c Microchip/TCPIPStack/WIFI/WFConnectionManager.c Microchip/TCPIPStack/WIFI/WFConnectionProfile.c Microchip/TCPIPStack/WIFI/WFDataTxRx.c Microchip/TCPIPStack/WIFI/WFDriverCom.c Microchip/TCPIPStack/WIFI/WFDriverRaw.c Microchip/TCPIPStack/WIFI/WFEventHandler.c Microchip/TCPIPStack/WIFI/WFInit.c Microchip/TCPIPStack/WIFI/WFMac.c Microchip/TCPIPStack/WIFI/WFMgmtMsg.c Microchip/TCPIPStack/WIFI/WFParamMsg.c Microchip/TCPIPStack/WIFI/WFPowerSave.c Microchip/TCPIPStack/WIFI/WFScan.c Microchip/TCPIPStack/WIFI/WFTxPower.c Microchip/TCPIPStack/WIFI/WF_Eint.c Microchip/TCPIPStack/WIFI/WF_Spi.c Microchip/TCPIPStack/WiFi/WF_pbkdf2.c Microchip/TCPIPStack/ARP.c Microchip/TCPIPStack/Announce.c Microchip/TCPIPStack/AutoIP.c Microchip/TCPIPStack/BerkeleyAPI.c Microchip/TCPIPStack/DHCP.c Microchip/TCPIPStack/DHCPs.c Microchip/TCPIPStack/DNS.c Microchip/TCPIPStack/DNSs.c Microchip/TCPIPStack/DynDNS.c Microchip/TCPIPStack/FTP.c Microchip/TCPIPStack/FileSystem.c Microchip/TCPIPStack/HTTP2.c Microchip/TCPIPStack/Hashes.c Microchip/TCPIPStack/Helpers.c Microchip/TCPIPStack/ICMP.c Microchip/TCPIPStack/IP.c Microchip/TCPIPStack/MPFS2.c Microchip/TCPIPStack/NBNS.c Microchip/TCPIPStack/RSA.c Microchip/TCPIPStack/Random.c Microchip/TCPIPStack/Reboot.c Microchip/TCPIPStack/SMTP.c Microchip/TCPIPStack/SNMP.c Microchip/TCPIPStack/SNMPv3.c Microchip/TCPIPStack/SNTP.c Microchip/TCPIPStack/SPIFlash.c Microchip/TCPIPStack/SSL.c Microchip/TCPIPStack/StackTsk.c Microchip/TCPIPStack/TCP.c Microchip/TCPIPStack/TCPPerformanceTest.c Microchip/TCPIPStack/TFTPc.c Microchip/TCPIPStack/Telnet.c Microchip/TCPIPStack/Tick.c Microchip/TCPIPStack/UDP.c Microchip/Transceivers/MRF24J40/MRF24J40.c Microchip/Transceivers/crc.c Microchip/Transceivers/security.c Microchip/WirelessProtocols/P2P/P2P.c Microchip/WirelessProtocols/SymbolTime.c MPack/mpack-common.c MPack/mpack-expect.c MPack/mpack-internal.c MPack/mpack-node.c MPack/mpack-platform.c MPack/mpack-reader.c MPack/mpack-writer.c MyFiles/MyCAN.c MyFiles/MyConsole.c MyFiles/MyFlash.c MyFiles/MyHTTP.c MyFiles/MyIO.c MyFiles/MyLED.c MyFiles/MyMDDFS.c MyFiles/MyMIWI.c MyFiles/MyRTCC.c MyFiles/MySPI.c MyFiles/MyTemperature.c MyFiles/MyWIFI.c MyFiles/MyCyclone.c MyFiles/MyApp.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Microchip/Common/TimeDelay.o: Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" -o ${OBJECTDIR}/Microchip/Common/TimeDelay.o Microchip/Common/TimeDelay.c   
	
${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o: Microchip/MDDFileSystem/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/MDDFileSystem 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d" -o ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o Microchip/MDDFileSystem/FSIO.c   
	
${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o: Microchip/MDDFileSystem/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/MDDFileSystem 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d" -o ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o Microchip/MDDFileSystem/SD-SPI.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o: Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o: Microchip/TCPIPStack/WIFI/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o Microchip/TCPIPStack/WIFI/WFConnectionManager.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o: Microchip/TCPIPStack/WIFI/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o Microchip/TCPIPStack/WIFI/WFConnectionProfile.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o: Microchip/TCPIPStack/WIFI/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o Microchip/TCPIPStack/WIFI/WFDataTxRx.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o: Microchip/TCPIPStack/WIFI/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o Microchip/TCPIPStack/WIFI/WFDriverCom.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o: Microchip/TCPIPStack/WIFI/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o Microchip/TCPIPStack/WIFI/WFDriverRaw.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o: Microchip/TCPIPStack/WIFI/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o Microchip/TCPIPStack/WIFI/WFEventHandler.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o: Microchip/TCPIPStack/WIFI/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o Microchip/TCPIPStack/WIFI/WFInit.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o: Microchip/TCPIPStack/WIFI/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o Microchip/TCPIPStack/WIFI/WFMac.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o: Microchip/TCPIPStack/WIFI/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o Microchip/TCPIPStack/WIFI/WFMgmtMsg.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o: Microchip/TCPIPStack/WIFI/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o Microchip/TCPIPStack/WIFI/WFParamMsg.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o: Microchip/TCPIPStack/WIFI/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o Microchip/TCPIPStack/WIFI/WFPowerSave.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o: Microchip/TCPIPStack/WIFI/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o Microchip/TCPIPStack/WIFI/WFScan.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o: Microchip/TCPIPStack/WIFI/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o Microchip/TCPIPStack/WIFI/WFTxPower.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o: Microchip/TCPIPStack/WIFI/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o Microchip/TCPIPStack/WIFI/WF_Eint.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o: Microchip/TCPIPStack/WIFI/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o Microchip/TCPIPStack/WIFI/WF_Spi.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o: Microchip/TCPIPStack/WiFi/WF_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o Microchip/TCPIPStack/WiFi/WF_pbkdf2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/ARP.o: Microchip/TCPIPStack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o Microchip/TCPIPStack/ARP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Announce.o: Microchip/TCPIPStack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o Microchip/TCPIPStack/Announce.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o: Microchip/TCPIPStack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o Microchip/TCPIPStack/AutoIP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o: Microchip/TCPIPStack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o Microchip/TCPIPStack/BerkeleyAPI.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o: Microchip/TCPIPStack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o Microchip/TCPIPStack/DHCP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o: Microchip/TCPIPStack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o Microchip/TCPIPStack/DHCPs.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DNS.o: Microchip/TCPIPStack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o Microchip/TCPIPStack/DNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o: Microchip/TCPIPStack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o Microchip/TCPIPStack/DNSs.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o: Microchip/TCPIPStack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o Microchip/TCPIPStack/DynDNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/FTP.o: Microchip/TCPIPStack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o Microchip/TCPIPStack/FTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o: Microchip/TCPIPStack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o Microchip/TCPIPStack/FileSystem.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o: Microchip/TCPIPStack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o Microchip/TCPIPStack/HTTP2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o: Microchip/TCPIPStack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o Microchip/TCPIPStack/Hashes.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o: Microchip/TCPIPStack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o Microchip/TCPIPStack/Helpers.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o: Microchip/TCPIPStack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o Microchip/TCPIPStack/ICMP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/IP.o: Microchip/TCPIPStack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/IP.o Microchip/TCPIPStack/IP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o: Microchip/TCPIPStack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o Microchip/TCPIPStack/MPFS2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o: Microchip/TCPIPStack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o Microchip/TCPIPStack/NBNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/RSA.o: Microchip/TCPIPStack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o Microchip/TCPIPStack/RSA.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Random.o: Microchip/TCPIPStack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Random.o Microchip/TCPIPStack/Random.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o: Microchip/TCPIPStack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o Microchip/TCPIPStack/Reboot.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o: Microchip/TCPIPStack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o Microchip/TCPIPStack/SMTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o: Microchip/TCPIPStack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o Microchip/TCPIPStack/SNMP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o: Microchip/TCPIPStack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o Microchip/TCPIPStack/SNMPv3.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o: Microchip/TCPIPStack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o Microchip/TCPIPStack/SNTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o: Microchip/TCPIPStack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o Microchip/TCPIPStack/SPIFlash.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SSL.o: Microchip/TCPIPStack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o Microchip/TCPIPStack/SSL.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o: Microchip/TCPIPStack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o Microchip/TCPIPStack/StackTsk.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TCP.o: Microchip/TCPIPStack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o Microchip/TCPIPStack/TCP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o: Microchip/TCPIPStack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o Microchip/TCPIPStack/TCPPerformanceTest.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o: Microchip/TCPIPStack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o Microchip/TCPIPStack/TFTPc.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o: Microchip/TCPIPStack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o Microchip/TCPIPStack/Telnet.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Tick.o: Microchip/TCPIPStack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o Microchip/TCPIPStack/Tick.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/UDP.o: Microchip/TCPIPStack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o Microchip/TCPIPStack/UDP.c   
	
${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o: Microchip/Transceivers/MRF24J40/MRF24J40.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o Microchip/Transceivers/MRF24J40/MRF24J40.c   
	
${OBJECTDIR}/Microchip/Transceivers/crc.o: Microchip/Transceivers/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/crc.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/crc.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/crc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/crc.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/crc.o Microchip/Transceivers/crc.c   
	
${OBJECTDIR}/Microchip/Transceivers/security.o: Microchip/Transceivers/security.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/security.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/security.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/security.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/security.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/security.o Microchip/Transceivers/security.c   
	
${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o: Microchip/WirelessProtocols/P2P/P2P.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d" -o ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o Microchip/WirelessProtocols/P2P/P2P.c   
	
${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o: Microchip/WirelessProtocols/SymbolTime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/WirelessProtocols 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d" -o ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o Microchip/WirelessProtocols/SymbolTime.c   
	
${OBJECTDIR}/MPack/mpack-common.o: MPack/mpack-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-common.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-common.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-common.o.d" -o ${OBJECTDIR}/MPack/mpack-common.o MPack/mpack-common.c   
	
${OBJECTDIR}/MPack/mpack-expect.o: MPack/mpack-expect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-expect.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-expect.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-expect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-expect.o.d" -o ${OBJECTDIR}/MPack/mpack-expect.o MPack/mpack-expect.c   
	
${OBJECTDIR}/MPack/mpack-internal.o: MPack/mpack-internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-internal.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-internal.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-internal.o.d" -o ${OBJECTDIR}/MPack/mpack-internal.o MPack/mpack-internal.c   
	
${OBJECTDIR}/MPack/mpack-node.o: MPack/mpack-node.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-node.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-node.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-node.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-node.o.d" -o ${OBJECTDIR}/MPack/mpack-node.o MPack/mpack-node.c   
	
${OBJECTDIR}/MPack/mpack-platform.o: MPack/mpack-platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-platform.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-platform.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-platform.o.d" -o ${OBJECTDIR}/MPack/mpack-platform.o MPack/mpack-platform.c   
	
${OBJECTDIR}/MPack/mpack-reader.o: MPack/mpack-reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-reader.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-reader.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-reader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-reader.o.d" -o ${OBJECTDIR}/MPack/mpack-reader.o MPack/mpack-reader.c   
	
${OBJECTDIR}/MPack/mpack-writer.o: MPack/mpack-writer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-writer.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-writer.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-writer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-writer.o.d" -o ${OBJECTDIR}/MPack/mpack-writer.o MPack/mpack-writer.c   
	
${OBJECTDIR}/MyFiles/MyCAN.o: MyFiles/MyCAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyCAN.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyCAN.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyCAN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyCAN.o.d" -o ${OBJECTDIR}/MyFiles/MyCAN.o MyFiles/MyCAN.c   
	
${OBJECTDIR}/MyFiles/MyConsole.o: MyFiles/MyConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyConsole.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyConsole.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyConsole.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyConsole.o.d" -o ${OBJECTDIR}/MyFiles/MyConsole.o MyFiles/MyConsole.c   
	
${OBJECTDIR}/MyFiles/MyFlash.o: MyFiles/MyFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyFlash.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyFlash.o.d" -o ${OBJECTDIR}/MyFiles/MyFlash.o MyFiles/MyFlash.c   
	
${OBJECTDIR}/MyFiles/MyHTTP.o: MyFiles/MyHTTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyHTTP.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyHTTP.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyHTTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyHTTP.o.d" -o ${OBJECTDIR}/MyFiles/MyHTTP.o MyFiles/MyHTTP.c   
	
${OBJECTDIR}/MyFiles/MyIO.o: MyFiles/MyIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyIO.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyIO.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyIO.o.d" -o ${OBJECTDIR}/MyFiles/MyIO.o MyFiles/MyIO.c   
	
${OBJECTDIR}/MyFiles/MyLED.o: MyFiles/MyLED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyLED.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyLED.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyLED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyLED.o.d" -o ${OBJECTDIR}/MyFiles/MyLED.o MyFiles/MyLED.c   
	
${OBJECTDIR}/MyFiles/MyMDDFS.o: MyFiles/MyMDDFS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyMDDFS.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyMDDFS.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyMDDFS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyMDDFS.o.d" -o ${OBJECTDIR}/MyFiles/MyMDDFS.o MyFiles/MyMDDFS.c   
	
${OBJECTDIR}/MyFiles/MyMIWI.o: MyFiles/MyMIWI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyMIWI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyMIWI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyMIWI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyMIWI.o.d" -o ${OBJECTDIR}/MyFiles/MyMIWI.o MyFiles/MyMIWI.c   
	
${OBJECTDIR}/MyFiles/MyRTCC.o: MyFiles/MyRTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyRTCC.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyRTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyRTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyRTCC.o.d" -o ${OBJECTDIR}/MyFiles/MyRTCC.o MyFiles/MyRTCC.c   
	
${OBJECTDIR}/MyFiles/MySPI.o: MyFiles/MySPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MySPI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MySPI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MySPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MySPI.o.d" -o ${OBJECTDIR}/MyFiles/MySPI.o MyFiles/MySPI.c   
	
${OBJECTDIR}/MyFiles/MyTemperature.o: MyFiles/MyTemperature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyTemperature.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyTemperature.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyTemperature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyTemperature.o.d" -o ${OBJECTDIR}/MyFiles/MyTemperature.o MyFiles/MyTemperature.c   
	
${OBJECTDIR}/MyFiles/MyWIFI.o: MyFiles/MyWIFI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyWIFI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyWIFI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyWIFI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyWIFI.o.d" -o ${OBJECTDIR}/MyFiles/MyWIFI.o MyFiles/MyWIFI.c   
	
${OBJECTDIR}/MyFiles/MyCyclone.o: MyFiles/MyCyclone.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyCyclone.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyCyclone.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyCyclone.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyCyclone.o.d" -o ${OBJECTDIR}/MyFiles/MyCyclone.o MyFiles/MyCyclone.c   
	
${OBJECTDIR}/MyFiles/MyApp.o: MyFiles/MyApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyApp.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyApp.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyApp.o.d" -o ${OBJECTDIR}/MyFiles/MyApp.o MyFiles/MyApp.c   
	
else
${OBJECTDIR}/Microchip/Common/TimeDelay.o: Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" -o ${OBJECTDIR}/Microchip/Common/TimeDelay.o Microchip/Common/TimeDelay.c   
	
${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o: Microchip/MDDFileSystem/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/MDDFileSystem 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o.d" -o ${OBJECTDIR}/Microchip/MDDFileSystem/FSIO.o Microchip/MDDFileSystem/FSIO.c   
	
${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o: Microchip/MDDFileSystem/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/MDDFileSystem 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o.d" -o ${OBJECTDIR}/Microchip/MDDFileSystem/SD-SPI.o Microchip/MDDFileSystem/SD-SPI.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o: Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.o Microchip/TCPIPStack/WIFI/WFConnectionAlgorithm.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o: Microchip/TCPIPStack/WIFI/WFConnectionManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionManager.o Microchip/TCPIPStack/WIFI/WFConnectionManager.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o: Microchip/TCPIPStack/WIFI/WFConnectionProfile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFConnectionProfile.o Microchip/TCPIPStack/WIFI/WFConnectionProfile.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o: Microchip/TCPIPStack/WIFI/WFDataTxRx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDataTxRx.o Microchip/TCPIPStack/WIFI/WFDataTxRx.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o: Microchip/TCPIPStack/WIFI/WFDriverCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverCom.o Microchip/TCPIPStack/WIFI/WFDriverCom.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o: Microchip/TCPIPStack/WIFI/WFDriverRaw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFDriverRaw.o Microchip/TCPIPStack/WIFI/WFDriverRaw.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o: Microchip/TCPIPStack/WIFI/WFEventHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFEventHandler.o Microchip/TCPIPStack/WIFI/WFEventHandler.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o: Microchip/TCPIPStack/WIFI/WFInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFInit.o Microchip/TCPIPStack/WIFI/WFInit.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o: Microchip/TCPIPStack/WIFI/WFMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMac.o Microchip/TCPIPStack/WIFI/WFMac.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o: Microchip/TCPIPStack/WIFI/WFMgmtMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFMgmtMsg.o Microchip/TCPIPStack/WIFI/WFMgmtMsg.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o: Microchip/TCPIPStack/WIFI/WFParamMsg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFParamMsg.o Microchip/TCPIPStack/WIFI/WFParamMsg.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o: Microchip/TCPIPStack/WIFI/WFPowerSave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFPowerSave.o Microchip/TCPIPStack/WIFI/WFPowerSave.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o: Microchip/TCPIPStack/WIFI/WFScan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFScan.o Microchip/TCPIPStack/WIFI/WFScan.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o: Microchip/TCPIPStack/WIFI/WFTxPower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WFTxPower.o Microchip/TCPIPStack/WIFI/WFTxPower.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o: Microchip/TCPIPStack/WIFI/WF_Eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Eint.o Microchip/TCPIPStack/WIFI/WF_Eint.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o: Microchip/TCPIPStack/WIFI/WF_Spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WIFI/WF_Spi.o Microchip/TCPIPStack/WIFI/WF_Spi.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o: Microchip/TCPIPStack/WiFi/WF_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/WiFi/WF_pbkdf2.o Microchip/TCPIPStack/WiFi/WF_pbkdf2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/ARP.o: Microchip/TCPIPStack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/ARP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/ARP.o Microchip/TCPIPStack/ARP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Announce.o: Microchip/TCPIPStack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Announce.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Announce.o Microchip/TCPIPStack/Announce.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o: Microchip/TCPIPStack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/AutoIP.o Microchip/TCPIPStack/AutoIP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o: Microchip/TCPIPStack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/BerkeleyAPI.o Microchip/TCPIPStack/BerkeleyAPI.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o: Microchip/TCPIPStack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DHCP.o Microchip/TCPIPStack/DHCP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o: Microchip/TCPIPStack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DHCPs.o Microchip/TCPIPStack/DHCPs.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DNS.o: Microchip/TCPIPStack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DNS.o Microchip/TCPIPStack/DNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o: Microchip/TCPIPStack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DNSs.o Microchip/TCPIPStack/DNSs.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o: Microchip/TCPIPStack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/DynDNS.o Microchip/TCPIPStack/DynDNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/FTP.o: Microchip/TCPIPStack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/FTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/FTP.o Microchip/TCPIPStack/FTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o: Microchip/TCPIPStack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/FileSystem.o Microchip/TCPIPStack/FileSystem.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o: Microchip/TCPIPStack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/HTTP2.o Microchip/TCPIPStack/HTTP2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o: Microchip/TCPIPStack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Hashes.o Microchip/TCPIPStack/Hashes.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o: Microchip/TCPIPStack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Helpers.o Microchip/TCPIPStack/Helpers.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o: Microchip/TCPIPStack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/ICMP.o Microchip/TCPIPStack/ICMP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/IP.o: Microchip/TCPIPStack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/IP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/IP.o Microchip/TCPIPStack/IP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o: Microchip/TCPIPStack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/MPFS2.o Microchip/TCPIPStack/MPFS2.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o: Microchip/TCPIPStack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/NBNS.o Microchip/TCPIPStack/NBNS.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/RSA.o: Microchip/TCPIPStack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/RSA.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/RSA.o Microchip/TCPIPStack/RSA.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Random.o: Microchip/TCPIPStack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Random.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Random.o Microchip/TCPIPStack/Random.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o: Microchip/TCPIPStack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Reboot.o Microchip/TCPIPStack/Reboot.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o: Microchip/TCPIPStack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SMTP.o Microchip/TCPIPStack/SMTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o: Microchip/TCPIPStack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNMP.o Microchip/TCPIPStack/SNMP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o: Microchip/TCPIPStack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNMPv3.o Microchip/TCPIPStack/SNMPv3.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o: Microchip/TCPIPStack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SNTP.o Microchip/TCPIPStack/SNTP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o: Microchip/TCPIPStack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SPIFlash.o Microchip/TCPIPStack/SPIFlash.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/SSL.o: Microchip/TCPIPStack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/SSL.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/SSL.o Microchip/TCPIPStack/SSL.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o: Microchip/TCPIPStack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/StackTsk.o Microchip/TCPIPStack/StackTsk.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TCP.o: Microchip/TCPIPStack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TCP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TCP.o Microchip/TCPIPStack/TCP.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o: Microchip/TCPIPStack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TCPPerformanceTest.o Microchip/TCPIPStack/TCPPerformanceTest.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o: Microchip/TCPIPStack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/TFTPc.o Microchip/TCPIPStack/TFTPc.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o: Microchip/TCPIPStack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Telnet.o Microchip/TCPIPStack/Telnet.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/Tick.o: Microchip/TCPIPStack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/Tick.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/Tick.o Microchip/TCPIPStack/Tick.c   
	
${OBJECTDIR}/Microchip/TCPIPStack/UDP.o: Microchip/TCPIPStack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIPStack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d 
	@${RM} ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/TCPIPStack/UDP.o.d" -o ${OBJECTDIR}/Microchip/TCPIPStack/UDP.o Microchip/TCPIPStack/UDP.c   
	
${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o: Microchip/Transceivers/MRF24J40/MRF24J40.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/MRF24J40/MRF24J40.o Microchip/Transceivers/MRF24J40/MRF24J40.c   
	
${OBJECTDIR}/Microchip/Transceivers/crc.o: Microchip/Transceivers/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/crc.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/crc.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/crc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/crc.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/crc.o Microchip/Transceivers/crc.c   
	
${OBJECTDIR}/Microchip/Transceivers/security.o: Microchip/Transceivers/security.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Transceivers 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/security.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Transceivers/security.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Transceivers/security.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/Transceivers/security.o.d" -o ${OBJECTDIR}/Microchip/Transceivers/security.o Microchip/Transceivers/security.c   
	
${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o: Microchip/WirelessProtocols/P2P/P2P.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o.d" -o ${OBJECTDIR}/Microchip/WirelessProtocols/P2P/P2P.o Microchip/WirelessProtocols/P2P/P2P.c   
	
${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o: Microchip/WirelessProtocols/SymbolTime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/WirelessProtocols 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d 
	@${RM} ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o.d" -o ${OBJECTDIR}/Microchip/WirelessProtocols/SymbolTime.o Microchip/WirelessProtocols/SymbolTime.c   
	
${OBJECTDIR}/MPack/mpack-common.o: MPack/mpack-common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-common.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-common.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-common.o.d" -o ${OBJECTDIR}/MPack/mpack-common.o MPack/mpack-common.c   
	
${OBJECTDIR}/MPack/mpack-expect.o: MPack/mpack-expect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-expect.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-expect.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-expect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-expect.o.d" -o ${OBJECTDIR}/MPack/mpack-expect.o MPack/mpack-expect.c   
	
${OBJECTDIR}/MPack/mpack-internal.o: MPack/mpack-internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-internal.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-internal.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-internal.o.d" -o ${OBJECTDIR}/MPack/mpack-internal.o MPack/mpack-internal.c   
	
${OBJECTDIR}/MPack/mpack-node.o: MPack/mpack-node.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-node.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-node.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-node.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-node.o.d" -o ${OBJECTDIR}/MPack/mpack-node.o MPack/mpack-node.c   
	
${OBJECTDIR}/MPack/mpack-platform.o: MPack/mpack-platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-platform.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-platform.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-platform.o.d" -o ${OBJECTDIR}/MPack/mpack-platform.o MPack/mpack-platform.c   
	
${OBJECTDIR}/MPack/mpack-reader.o: MPack/mpack-reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-reader.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-reader.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-reader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-reader.o.d" -o ${OBJECTDIR}/MPack/mpack-reader.o MPack/mpack-reader.c   
	
${OBJECTDIR}/MPack/mpack-writer.o: MPack/mpack-writer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MPack 
	@${RM} ${OBJECTDIR}/MPack/mpack-writer.o.d 
	@${RM} ${OBJECTDIR}/MPack/mpack-writer.o 
	@${FIXDEPS} "${OBJECTDIR}/MPack/mpack-writer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MPack/mpack-writer.o.d" -o ${OBJECTDIR}/MPack/mpack-writer.o MPack/mpack-writer.c   
	
${OBJECTDIR}/MyFiles/MyCAN.o: MyFiles/MyCAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyCAN.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyCAN.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyCAN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyCAN.o.d" -o ${OBJECTDIR}/MyFiles/MyCAN.o MyFiles/MyCAN.c   
	
${OBJECTDIR}/MyFiles/MyConsole.o: MyFiles/MyConsole.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyConsole.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyConsole.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyConsole.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyConsole.o.d" -o ${OBJECTDIR}/MyFiles/MyConsole.o MyFiles/MyConsole.c   
	
${OBJECTDIR}/MyFiles/MyFlash.o: MyFiles/MyFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyFlash.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyFlash.o.d" -o ${OBJECTDIR}/MyFiles/MyFlash.o MyFiles/MyFlash.c   
	
${OBJECTDIR}/MyFiles/MyHTTP.o: MyFiles/MyHTTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyHTTP.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyHTTP.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyHTTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyHTTP.o.d" -o ${OBJECTDIR}/MyFiles/MyHTTP.o MyFiles/MyHTTP.c   
	
${OBJECTDIR}/MyFiles/MyIO.o: MyFiles/MyIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyIO.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyIO.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyIO.o.d" -o ${OBJECTDIR}/MyFiles/MyIO.o MyFiles/MyIO.c   
	
${OBJECTDIR}/MyFiles/MyLED.o: MyFiles/MyLED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyLED.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyLED.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyLED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyLED.o.d" -o ${OBJECTDIR}/MyFiles/MyLED.o MyFiles/MyLED.c   
	
${OBJECTDIR}/MyFiles/MyMDDFS.o: MyFiles/MyMDDFS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyMDDFS.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyMDDFS.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyMDDFS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyMDDFS.o.d" -o ${OBJECTDIR}/MyFiles/MyMDDFS.o MyFiles/MyMDDFS.c   
	
${OBJECTDIR}/MyFiles/MyMIWI.o: MyFiles/MyMIWI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyMIWI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyMIWI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyMIWI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyMIWI.o.d" -o ${OBJECTDIR}/MyFiles/MyMIWI.o MyFiles/MyMIWI.c   
	
${OBJECTDIR}/MyFiles/MyRTCC.o: MyFiles/MyRTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyRTCC.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyRTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyRTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyRTCC.o.d" -o ${OBJECTDIR}/MyFiles/MyRTCC.o MyFiles/MyRTCC.c   
	
${OBJECTDIR}/MyFiles/MySPI.o: MyFiles/MySPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MySPI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MySPI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MySPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MySPI.o.d" -o ${OBJECTDIR}/MyFiles/MySPI.o MyFiles/MySPI.c   
	
${OBJECTDIR}/MyFiles/MyTemperature.o: MyFiles/MyTemperature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyTemperature.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyTemperature.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyTemperature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyTemperature.o.d" -o ${OBJECTDIR}/MyFiles/MyTemperature.o MyFiles/MyTemperature.c   
	
${OBJECTDIR}/MyFiles/MyWIFI.o: MyFiles/MyWIFI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyWIFI.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyWIFI.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyWIFI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyWIFI.o.d" -o ${OBJECTDIR}/MyFiles/MyWIFI.o MyFiles/MyWIFI.c   
	
${OBJECTDIR}/MyFiles/MyCyclone.o: MyFiles/MyCyclone.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyCyclone.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyCyclone.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyCyclone.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyCyclone.o.d" -o ${OBJECTDIR}/MyFiles/MyCyclone.o MyFiles/MyCyclone.c   
	
${OBJECTDIR}/MyFiles/MyApp.o: MyFiles/MyApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MyFiles 
	@${RM} ${OBJECTDIR}/MyFiles/MyApp.o.d 
	@${RM} ${OBJECTDIR}/MyFiles/MyApp.o 
	@${FIXDEPS} "${OBJECTDIR}/MyFiles/MyApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"MyIncludes" -I"MyConfig" -I"MyConfig/MyConfig_MIWI" -I"MyConfig/MyConfig_WIFI" -I"MyConfig/MyConfig_MDDFS" -I"Microchip/Include" -I"MyWeb" -I"MPack" -MMD -MF "${OBJECTDIR}/MyFiles/MyApp.o.d" -o ${OBJECTDIR}/MyFiles/MyApp.o MyFiles/MyApp.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=64000
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=64000
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic32software.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
