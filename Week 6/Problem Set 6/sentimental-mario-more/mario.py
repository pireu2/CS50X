while True:
    try:
        n = int(input("Height: "))
        if n > 8 or n < 1:
            raise ValueError
    except ValueError:
        continue
    else:
        break
for i in range(1, n + 1):
    print(" " * (n - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
