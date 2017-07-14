dtb-$(CONFIG_XILFPGA_NEXYS4DDR)	+= nexys4ddr.dtb
dtb-$(CONFIG_XILFPGA_DE10LITE)	+= de10lite.dtb

obj-y				+= $(patsubst %.dtb, %.dtb.o, $(dtb-y))

# Force kbuild to make empty built-in.o if necessary
obj-				+= dummy.o

always				:= $(dtb-y)
clean-files	:= *.dtb *.dtb.S
