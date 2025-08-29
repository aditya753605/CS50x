text = input("Text: ")
letter = sum (1 for c in text if c.isalpha())
words = len(text.split())
sentences = sum(1 for c in text if c in ".!?")

L = letter / words * 100
S = sentences / words * 100

index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
