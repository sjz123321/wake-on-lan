# wake-on-lan

## Dependence
linux 

netcat >=1.10

## Compile

`git clone https://github.com/sjz123321/wake-on-lan.git && cd ./wake-on-lan/`

`gcc -std=c99 netwake.c -o netwake`

Then you can install it `sudo mv netwake /usr/bin/`

## Usage

netwake [MAC Address(aa:bb:cc:dd:ee:ff)] [IP Address] [addtional options...]

	-b [Boardcast Address]
  
	-c Number of packets will be sent default: 4 
  
	-h display this help 
  

