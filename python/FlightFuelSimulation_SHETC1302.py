import random

#Choose Plane Type
print "A:747-400-Domestic"
print "B:767-300-Freighter"
print "C:777-300-Freighter"

PlaneType=raw_input("Please choose one of the plane above (enter the letter):")

if PlaneType == "A":
    print "The maximum fule capacity: 53,985gal/204,355L"
elif PlaneType == "B":
    print "The maximum fule capacity: 23,980gal/90,770L"
else:
    print "The maximum fule capacity: 47,890gal/181,280L"

#Choose Destination
print "\nA:Shanghai"
print "B:London"
print "C:Edmonton"

Destination=raw_input("Please choose one of the Destination above (enter the letter):")

if Destination == "A":
    print "The distance from Vancouver to Shanghai: 9061km"
elif Destination == "B":
    print "The distance from Vancouver to London: 7581km"
else:
    print "The distance from Vancouver to Edmoton: 811km"

#Number of Passengers and Baggage
print "\nAssume each adult is 70 kg and child(under 14-year-old) is 40kg."
print "Assume each registered luggages is 23kg and each carry-on luggages 5kg."
def PBW(x,y,z,w):  #x=Adult, y=Children, z=Registered luggage, w=Carry-on luggage
    PBW=70*x+40*y+23*z+5*w
    return PBW
x1=int(raw_input("The total number of adults(include crew):"))
y1=int(raw_input("The total number of children:"))
z=int(raw_input("The total number of registered luggages:"))
w=int(raw_input("The total number of carry-on luggages:"))
num=PBW(x1,y1,z,w)
print "The total weight of passenger and baggage are",str(num),"kg."

#Maximum Capacity Calculation - Takeoff 
def Exceeds(x,y):
    Exceeds = x - y  #x=maximum capacity, y=payload
    if Exceeds <= 0:
        print "The total weight exceeds the maximum capacity of this flight."
        #Suggestions
        print "\nThere are two options for your plan:"
        people = int((y-x)/70)
        print "1:Let"+str(people)+"take another plan."
        print "2:Take a half of fuel and refueled later.\n"
    else:
        print "The plane could fly safely.\n"
    return Exceeds

if PlaneType == "A":
    x = 111605
    Exceeds(x, num)
elif PlaneType == "B":
    x = 52700
    Exceeds(x,num)
else:
    x = 112000
    Exceeds(x,num)

#Land Safety
if PlaneType == "A":
    if Destination == "A":
        print "The plan has to be refueled 3 times."
        print "Advice: Don't fly to Shanghai by Boeing 747-400-Domestic."
    elif Destination == "B":
        print "The plan has to be refueled 2 times."
        print "Advice: Don't fly to London by Boeing 747-400-Domestic."
    else:
        print "The fuel is enough flying to Edmonton!"
elif PlaneType == "B":
    if Destination == "A":
        print "The plan has to be refueled 1 times."
        print "Advice: Refueled at air,because the plan has to across Pacific Ocean."
    elif Destination == "B":
        print "The plan has to be refueled 1 times."
        print "Advice: Refueled at Monteral."
    else:
        print "The fuel is enough flying to Edmonton!"
else:
    if PlaneType == "C":
        print "The fuel is enough!"

#Unexpected 6 Factors
print "\nRandom Factor"
def UF(x):
    x=random.randrange(1,7)
    if x == 1:
        print "There is a ThunderStorm happened, please connect to control tower to land on the farther airport."
    elif x == 2:
        print "There is a EarthQuake happened, please connect to control tower to land on the farther airport."
    elif x == 3:
        print "The airport is closed somehow, please connect to control tower to land on the closer airport."
    elif x == 4:
        print "It is too foggy to land, please connect to control tower to land on the closer airport."
    elif x == 5:
        print "The Civil War happened in destination, please connect to control tower waiting the command."
    else:
        print "The plane is oil leak, please connect to control tower to send a refuelling plane and land as soon as possible."
    return x
UF(x)

#Display all results
#Fuel Consumption
if PlaneType == "A":
    if Destination == "A":
        FC747=float(x1+y1)*(9061/100)*3.1
        print "The Fuel Consumption is:", FC747, "L"
    elif Destination == "B":
        FC747 = float(x1+y1)*(7581/100)*3.1
        print "The Fuel Consumption is:", FC747, "L"
    else:
        FC747 = float(x1+y1)*(811/100)*3.1
        print "The Fuel Consumption is:", FC747, "L"
elif PlaneType == "B":
    if Destination == "A":
        FC767 = float(x1+y1)*(9061/100)*6.94
        print "The Fuel Consumption is:", FC767, "L"
    elif Destination == "B":
        FC767 = float(x1+y1)*(7581/100)*6.94
        print "The Fuel Consumption is:", FC767, "L"
    else:
        FC767 = float(x1+y1)*(811/100)*6.94
        print "The Fuel Consumption is:", FC767, "L"
else:
    if PlaneType == "C":
        if Destination == "A":
            FC777 = float(x1+y1)*(9061/100)*8.12
            print "The Fuel Consumption is:", FC777, "L"
        elif Destination == "B":
            FC777 = float(x1+y1)*(7581/100)*8.12
            print "The Fuel Consumption is:", FC777, "L"
        else:
            FC777 = float(x1+y1)*(811/100)*8.12
            print "The Fuel Consumption is:", FC777, "L"
#Total Passengers and Baggages
TP = x1+y1
print "Total Passengers are:", TP
TB = w+z
print "Total Baggages are:", TB
#Destination and Distance
if Destination == "A":
    print "The distance from Vancouver to Shanghai: 9061km"
elif Destination == "B":
    print "The distance from Vancouver to London: 7581km"
else:
    print "The distance from Vancouver Edmonton: 811km"
