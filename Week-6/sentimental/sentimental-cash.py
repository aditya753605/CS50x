while True:
    cash = float(input("Change: "))
    if cash >= 0:
        break

cents = round(cash * 100)
penny = 1
nickel = 5
dime = 10
quater = 25
count = 0

if cents == 0:
    print("0")
else:
    for coin in [quater, dime, nickel, penny]:
        count += cents // coin
        cents %= coin

print(count)

