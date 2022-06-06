from smbus import SMBus
from time import sleep
import requests

def plantState(pv):
    p = int(pv)

    if(p<=75 and p!=0):
        return True

def errorMessage(msg):
    d = {}
    d['msg'] = msg
    requests.post("https://maker.ifttt.com/trigger/pumpsys5/json/with/key/dvTlGRl_Yvr1Vrv4GnGeuc",
                  data=d)

def main():
    bus = SMBus(1)
    addr = 0x8
    ctrl = 1

    haveWatered = 0
    prevMoist = 0
    delay = 30

    print()
    print("I2C Primary Program for SIT201 for Project - Raspberry Pi ")
    print("Corey James Bock")
    print()

    while True:
        print()
        print("Communicating with Group 1")
        try:
            smReading = (bus.read_byte(addr)*4)

            if(smReading == 0):
                errorMessage("Error with SMS response. Check Group 1")

            if(plantState(smReading)):
                prevMoist = smReading
                print("Plant requires watering")
                print()
                print("Communicating with Group 2")
                try:

                    if haveWatered == 1:
                        if prevMoist == smReading:
                            # Plant moisture has not changed in a cycle, flag potential error with pump.
                            print("Plant moisture was ", prevMoist, "at last reading and now is ", smReading,
                                  ". There is a problem")
                            requests.post(
                                "https://maker.ifttt.com/trigger/pumpsys4/json/with/key/dvTlGRl_Yvr1Vrv4GnGeuc")
                    
                    bus.write_byte(0x9, 0x1)
                    sleep(5)
                    try:
                        resp = bus.read_byte(0x9)

                        # 1 return means pump ran
                        # 2 return means no water
                        # 3 return means pump ran but ran out of water

                        if resp == 0:
                            print("Pump system isn't ready")
                        elif resp == 1:
                            print("Pump ran full cycle.")
                            haveWatered = 1;
                            requests.post("https://maker.ifttt.com/trigger/pumpsys1/json/with/key/dvTlGRl_Yvr1Vrv4GnGeuc")
                        elif resp == 2:
                            print("No water available to pump.")
                            requests.post("https://maker.ifttt.com/trigger/pumpsys2/json/with/key/dvTlGRl_Yvr1Vrv4GnGeuc")
                        elif resp == 3:
                            print("Pump ran out of water while active.")
                            haveWatered = 1
                            requests.post("https://maker.ifttt.com/trigger/pumpsys3/json/with/key/dvTlGRl_Yvr1Vrv4GnGeuc")
                        else:
                            print("Unknown return value from pump system: "+resp)

                        sleep(delay)

                    except IOError:
                        errorMessage("Error communicating with Group 2. Check System")
                        sleep(delay)

                except IOError:
                    errorMessage("Error communicating with Group 2. Check System")
                    sleep(delay)
            else:
                print("Plant doesn't need watering")
                sleep(delay)

        except IOError:
            errorMessage("Error communicating with Group 1. Check System")
            sleep(delay)

if __name__ == '__main__':
    try:
        main()

    except KeyboardInterrupt:
        print()
        print("Program terminated by user")
