--LuaPlayer Euphoria IntraFont Sample
--By Zack - www.retroemu.com

--Assign all available colors to a table (makes life easier)
IntraCol = {black = 0, red = 1, blue = 2, white = 3, lightGrey = 4, grey = 5, darkGrey = 6, purple = 7, yellow  = 8, orange = 9, transparent = 10}

--Load our background Image
backGround = Image.createEmpty(480, 272)
backGround:clear(Color.new(255, 255, 255))

--Load a Font using IntraFont
font = IntraFont.load("font.pgf")

oldpad = Controls.readPeek()

while not Controls.readPeek():start() do

	pad = Controls.readPeek()

	--Initialize the GU (Note : Any graphical functions MUST be placed AFTER this)
	System.draw()
	
	--Clear the screen
	screen:clear()
	
	screen:blit(0, 0, backGround)
	
	--Print some text using IntraFont	
	IntraFont.print(font, 20, 120, 1.0, IntraCol.white, IntraCol.black, "hello")
	IntraFont.print(font, 20, 150, 0.6, IntraCol.white, IntraCol.black, "welcome to luaplayer euphoria")
	
	--Finish the GU and Sync
	System.endDraw()
	
	--Show the FPS (Note : MUST be called after System.endGU()
	System.showFPS()
	--Flip buffers
	screen.flip()
end

IntraFont.unLoad()
System.quit() -- Quit the application after the main loop breaks
