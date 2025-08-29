while True:
    card_number = int(input("Number: "))
    if card_number > 0:
        break

number = card_number
sum1 = 0
sum2 = 0

isSecond = False
while number > 0:
    digit = number % 10
    if isSecond:
        product = digit * 2
        if product > 9:
            product -= 9
        sum2 += product
    else:
        sum1 += digit
    isSecond = not isSecond
    number //= 10

check_sum = sum1 +sum2

if check_sum % 10 != 0:
    print("INVALID")

else:
    temp = card_number
    count = 0
    while temp > 100:
        temp //= 10
        count += 1
    start_value = temp
    count += 2
    
    if count == 15 and start_value in (34,37):
        print("AMEX")
    elif count == 16 and 51 <= start_value <= 55:
        print("Mastercard")
    elif count in (13,16) and start_value // 10 == 4:
        print("VISA")
    else:
        print("INVALID")
