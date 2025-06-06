import tkinter as tk

textBoxWidth = 20
textBoxWidthSmall = 20

sdd = tk.Tk()

file_name = "search.dat" # replace with the name of your file
backup_name = "searchBC.dat" # replace with the name of your backup file

file = open(file_name, "r")
backup = open(backup_name, "w")

lines = file.readlines()

backup.writelines(lines)
backup.close

txt1_1,str1 = lines[0].split(maxsplit=1)
txt2_1,str2 = lines[1].split(maxsplit=1)
txt3_1,str3 = lines[2].split(maxsplit=1)
txt4_1,str4 = lines[3].split(maxsplit=1)
txt5_1,txt5_2,str5 = lines[4].split(maxsplit=2)
txt6_1,txt6_2,txt6_3,txt6_4,str6 = lines[5].split(maxsplit=4)
txt7_1,txt7_2,txt7_3,str7 = lines[6].split(maxsplit=3)
txt8_1,txt8_2,str8 = lines[7].split(maxsplit=2)
txt9_1,txt9_2,txt9_3,str9 = lines[8].split(maxsplit=3)
txt10_1,txt10_2,txt10_3,str10 = lines[9].split(maxsplit=3)
txt11_1,str11 = lines[10].split(maxsplit=1)
txt12_1,txt12_2,txt12_3,str12 = lines[11].split(maxsplit=3)
txt13_1,txt13_2,str13 = lines[12].split(maxsplit=2)
txt14_1,txt14_2,str14 = lines[13].split(maxsplit=2)
txt15_1,str15 = lines[14].split(maxsplit=1)

file.close

entry_text1_1 = tk.StringVar()
entry_text2_1 = tk.StringVar()
entry_text3_1 = tk.StringVar()
entry_text4_1 = tk.StringVar()
entry_text5_1 = tk.StringVar()
entry_text5_2 = tk.StringVar()
entry_text6_1 = tk.StringVar()
entry_text6_2 = tk.StringVar()
entry_text6_3 = tk.StringVar()
entry_text6_4 = tk.StringVar()
entry_text7_1 = tk.StringVar()
entry_text7_2 = tk.StringVar()
entry_text7_3 = tk.StringVar()
entry_text8_1 = tk.StringVar()
entry_text8_2 = tk.StringVar()
entry_text9_1 = tk.StringVar()
entry_text9_2 = tk.StringVar()
entry_text9_3 = tk.StringVar()
entry_text10_1 = tk.StringVar()
entry_text10_2 = tk.StringVar()
entry_text10_3 = tk.StringVar()
entry_text11_1 = tk.StringVar()
entry_text12_1 = tk.StringVar()
entry_text12_2 = tk.StringVar()
entry_text12_3 = tk.StringVar()
entry_text13_1 = tk.StringVar()
entry_text13_2 = tk.StringVar()
entry_text14_1 = tk.StringVar()
entry_text14_2 = tk.StringVar()
entry_text15_1 = tk.StringVar()


def reset():
    entry_text1_1.set(txt1_1)
    entry_text2_1.set(txt2_1)
    entry_text3_1.set(txt3_1)
    entry_text4_1.set(txt4_1)
    entry_text5_1.set(txt5_1)
    entry_text5_2.set(txt5_2)
    entry_text6_1.set(txt6_1)
    entry_text6_2.set(txt6_2)
    entry_text6_3.set(txt6_3)
    entry_text6_4.set(txt6_4)
    entry_text7_1.set(txt7_1)
    entry_text7_2.set(txt7_2)
    entry_text7_3.set(txt7_3)
    entry_text8_1.set(txt8_1)
    entry_text8_2.set(txt8_2)
    entry_text9_1.set(txt9_1)
    entry_text9_2.set(txt9_2)
    entry_text9_3.set(txt9_3)
    entry_text10_1.set(txt10_1)
    entry_text10_2.set(txt10_2)
    entry_text10_3.set(txt10_3)
    entry_text11_1.set(txt11_1)
    entry_text12_1.set(txt12_1)
    entry_text12_2.set(txt12_2)
    entry_text12_3.set(txt12_3)
    entry_text13_1.set(txt13_1)
    entry_text13_2.set(txt13_2)
    entry_text14_1.set(txt14_1)
    entry_text14_2.set(txt14_2)
    entry_text15_1.set(txt15_1)

reset()


sdd.title("Search dot dat")
sdd.geometry('720x360')

label1 = tk.Label(sdd, text = "1. Location of data input files")
label1.grid(column=5,row=1, sticky = 'w')

text1_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text1_1)
text1_1.grid(column=1,row=1)



label2 = tk.Label(sdd, text = "2. Location of PSD input files")
label2.grid(column=5,row=2, sticky = 'w')

text2_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text2_1)
text2_1.grid(column=1,row=2)



label3 = tk.Label(sdd, text = "3. Location of ACF input files")
label3.grid(column=5,row=3, sticky = 'w')

text3_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text3_1)
text3_1.grid(column=1,row=3)



label4 = tk.Label(sdd, text = "4. Location of prior CDF input files")
label4.grid(column=5,row=4, sticky = 'w')

text4_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text4_1)
text4_1.grid(column=1,row=4)



label5 = tk.Label(sdd, text = "5. Sanity checks? Binary Files?")
label5.grid(column=5,row=5, sticky = 'w')

text5_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text5_1)
text5_1.grid(column=1,row=5)

text5_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text5_2)
text5_2.grid(column=2,row=5)



label6 = tk.Label(sdd, text = "6. Week/day range (W1 D1 W2 D2)")
label6.grid(column=5,row=6, sticky = 'w')

text6_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text6_1)
text6_1.grid(column=1,row=6)

text6_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text6_2)
text6_2.grid(column=2,row=6)

text6_3 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text6_3)
text6_3.grid(column=3,row=6)

text6_4 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text6_4)
text6_4.grid(column=4,row=6)



label7 = tk.Label(sdd, text = "7. event invest? event ep, half-JW")
label7.grid(column=5,row=7, sticky = 'w')

text7_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text7_1)
text7_1.grid(column=1,row=7)

text7_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text7_2)
text7_2.grid(column=2,row=7)

text7_3 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text7_3)
text7_3.grid(column=3,row=7)



label8 = tk.Label(sdd, text = "8. afc_label")
label8.grid(column=5,row=8, sticky = 'w')

text8_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text5_1)
text8_1.grid(column=1,row=8)

text8_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text5_2)
text8_2.grid(column=2,row=8)



label9 = tk.Label(sdd, text = "9. exact, Detrend & difference (idiff)")
label9.grid(column=5,row=9, sticky = 'w')

text9_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text9_1)
text9_1.grid(column=1,row=9)

text9_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text9_2)
text9_2.grid(column=2,row=9)

text9_3 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text9_3)
text9_3.grid(column=3,row=9)



label10 = tk.Label(sdd, text = "10. model, R(/Rgps), alpha/pi")
label10.grid(column=5,row=10, sticky = 'w')

text10_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text10_1)
text10_1.grid(column=1,row=10)

text10_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text10_2)
text10_2.grid(column=2,row=10)

text10_3 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text10_3)
text10_3.grid(column=3,row=10)



label11 = tk.Label(sdd, text = "11. Assume coupling?")
label11.grid(column=5,row=11, sticky = 'w')

text11_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text11_1)
text11_1.grid(column=1,row=11)



label12 = tk.Label(sdd, text = "12. NMC, param NMC, hmin")
label12.grid(column=5,row=12, sticky = 'w')

text12_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text12_1)
text12_1.grid(column=1,row=12)

text12_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text12_2)
text12_2.grid(column=2,row=12)

text12_3 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text12_3)
text12_3.grid(column=3,row=12)



label13 = tk.Label(sdd, text = "13. O_cut, SNR_cut")
label13.grid(column=5,row=13, sticky = 'w')

text13_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text13_1)
text13_1.grid(column=1,row=13)

text13_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text13_2)
text13_2.grid(column=2,row=13)



label14 = tk.Label(sdd, text = "14. Limit # cores (0=no), //ise iterations?")
label14.grid(column=5,row=14, sticky = 'w')

text14_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text14_1)
text14_1.grid(column=1,row=14)

text14_2 = tk.Entry(sdd, width = textBoxWidthSmall, textvariable=entry_text14_2)
text14_2.grid(column=2,row=14)



label15 = tk.Label(sdd, text = "15. label for output files")
label15.grid(column=5,row=15, sticky = 'w')

text15_1 = tk.Entry(sdd, width = textBoxWidth, textvariable=entry_text15_1)
text15_1.grid(column=1,row=15)

def save():
    file = open(file_name, "w")
    file.write(entry_text1_1.get())
    file.write("          ")
    file.writelines(str1)
    file.write(entry_text2_1.get())
    file.write("             ")
    file.writelines(str2)
    file.write(entry_text3_1.get())
    file.write("             ")
    file.writelines(str3)
    file.write(entry_text4_1.get())
    file.write("         ")
    file.writelines(str4)
    file.write(entry_text5_1.get())
    file.write(" ")
    file.write(entry_text5_2.get())
    file.write("                 ")
    file.writelines(str5)
    file.write(entry_text6_1.get())
    file.write(" ")
    file.write(entry_text6_2.get())
    file.write(" ")
    file.write(entry_text6_3.get())
    file.write(" ")
    file.write(entry_text6_4.get())
    file.write("        ")
    file.writelines(str6)
    file.write(entry_text7_1.get())
    file.write(" ")
    file.write(entry_text7_2.get())
    file.write(" ")
    file.write(entry_text7_3.get())
    file.write("           ")
    file.writelines(str7)
    file.write(entry_text8_1.get())
    file.write(" ")
    file.write(entry_text8_2.get())
    file.write("           ")
    file.writelines(str8)
    file.write(entry_text9_1.get())
    file.write(" ")
    file.write(entry_text9_2.get())
    file.write(" ")
    file.write(entry_text9_3.get())
    file.write("               ")
    file.writelines(str9)
    file.write(entry_text10_1.get())
    file.write("  ")
    file.write(entry_text10_2.get())
    file.write("  ")
    file.write(entry_text10_3.get())
    file.write("      ")
    file.writelines(str10)
    file.write(entry_text11_1.get())
    file.write("                 ")
    file.writelines(str11)
    file.write(entry_text12_1.get())
    file.write(" ")
    file.write(entry_text12_2.get())
    file.write(" ")
    file.write(entry_text12_3.get())
    file.write("      ")
    file.writelines(str12)
    file.write(entry_text13_1.get())
    file.write(" ")
    file.write(entry_text13_2.get())
    file.write("             ")
    file.writelines(str13)
    file.write(entry_text14_1.get())
    file.write("  ")
    file.write(entry_text14_2.get())
    file.write("                ")
    file.writelines(str14)
    file.write(entry_text15_1.get())
    file.write("          ")
    file.writelines(str15)
    file.write("====================/")
    
    file.close

button1 = tk.Button(sdd, text = "Save", fg = "black", command=save)
button1.grid(column=1,row=17)


button2 = tk.Button(sdd, text = "Reset", fg = "black", command=reset)
button2.grid(column=2,row=17)

sdd.mainloop()