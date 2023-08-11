def main():
    while True:
        try:
            card = input("Number: ")
            int(card)
        except ValueError:
            continue
        else:
            break
    if checksum(card) != 0:
        print("INVALID")
    else:
        print(identify(card))


def checksum(str):
    list = str[-2::-2]
    sum = 0
    for i in list:
        number = int(i) * 2
        if number > 9:
            sum += int(number / 10) + int(number % 10)
        else:
            sum += number

    list = str[-1::-2]
    for i in list:
        sum += int(i)

    return sum % 10


def identify(n):
    if len(n) == 15:
        if n[:2] == "34" or n[:2] == "37":
            return "AMEX"
        else:
            return "INVALID"
    elif len(n) == 16:
        if n[:1] == "4":
            return "VISA"
        elif n[0] == "5" and n[1] in ["1", "2", "3", "4", "5"]:
            return "MASTERCARD"
        else:
            return "INVALID"
    elif len(n) == 13:
        if n[:1] == "4":
            return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
