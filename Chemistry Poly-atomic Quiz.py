import random
fowardPoly = {"Nitrate":"NO3-",
              "Nitrite":"NO2-",
              "Chromate":"CrO4-2",
              "Dichromate":"Cr2O7-2",
              "Cyanide":"CN-",
              "Permanganate":"MnO4-",
              "Hydroxide":"OH-",
              "Carbonate":"CO3-2",
              "Sulfate":"SO4-2",
              "Sulfite":"SO3-2",
              "Oxalate":"C2O4-2",
              "Phosphate":"PO4-3",
              "Acetate":"C2H3O2-",
              "Perchlorate":"ClO4-",
              "Chlorate":"ClO3-",
              "Chlorite":"ClO2-",
              "Hypochlorite":"ClO-",
              "Hydrogen Carbonate (AKA bicarbonate)":"HCO3-",
              "Thiocyanate":"SCN-",
              "Ammonium":"NH4+"}
index = ["Nitrate",
              "Nitrite",
              "Chromate",
              "Dichromate",
              "Cyanide",
              "Permanganate",
              "Hydroxide",
              "Carbonate",
              "Sulfate",
              "Sulfite",
              "Oxalate",
              "Phosphate",
              "Acetate",
              "Perchlorate",
              "Chlorate",
              "Chlorite",
              "Hypochlorite",
              "Hydrogen Carbonate (AKA bicarbonate)",
              "Thiocyanate",
              "Ammonium"]
def printWel():
              print("""Welcome to the Chemistry Poly-Atomic Quiz
              
              0: Exits
              1: Start quiz in order
              2: Start quiz in random order
              """)
              
#Start of the program
length = 0
printWel()
num = int(input("Enter a number: "))
while num != 0:
              if num == 1:
                            for i in fowardPoly:
                                          print("What is", index[i], "?")
                                          answer = input("")
                                          if answer == fowardPoly[index[i]]:
                                                        print("CORRECT!")
                                          else:
                                                        print("WRONG!")
                                          
