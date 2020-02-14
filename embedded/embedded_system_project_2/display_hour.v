module count_display_hour (clk, reset, enable, display, display10,stop_enable_sec,stopwatch,add_hour);
	parameter N=24, M=5;
	input clk, reset, enable,stop_enable_sec,add_hour,stopwatch;
	output [6:0] display, display10;
	reg [M-1:0] bcd;
	reg [6:0] display, display10;
	integer a,hr,hr10,check;

	always @(posedge clk or posedge reset) begin
		if (reset) begin
			bcd = 0;
			hr=0;
			hr10=0;
			display = 7'b000_0001;
			display10 = 7'b000_0001;
		end
		else if(stopwatch & (check==0))begin
				display = 7'b000_0001;
				display10 = 7'b000_0001;
				check=1;
		end
		else if(add_hour) begin 
		if(a == 49999999) begin
				a=0;
				if(bcd == N-1) begin bcd = 0; hr10 = 0; hr = 0; end
				else begin 
					bcd = bcd + 1;
					if(bcd < 10) begin hr10 = 0; hr = bcd; end
					else if(bcd < 20) begin hr10 = 1; hr = bcd - 10; end
					else begin hr10 = 2; hr = bcd - 20; end
				end
				if(!stop_enable_sec)begin
					case (hr)
						0:display = 7'b000_0001;
						1:display = 7'b100_1111;
						2:display = 7'b001_0010;
						3:display = 7'b000_0110;
						4:display = 7'b100_1100;
						5:display=  7'b010_0100;
						6:display = 7'b010_0000;
						7:display = 7'b000_1111;
						8:display = 7'b000_0000;
						9:display = 7'b000_0100;
						default: display = 7'b100_1111;
					endcase
					case (hr10)
						0:display10 = 7'b000_0001;
						1:display10 = 7'b100_1111;
						2:display10 = 7'b001_0010;
						default: display10 = 7'b100_1111;
					endcase
				end
			end
			else
				a = a + 1;
		end
		else if(enable) begin
			if(a == 49999999) begin
				a=0;
				if(bcd == N-1) begin bcd = 0; hr10 = 0; hr = 0; end
				else begin 
					bcd = bcd + 1;
					if(bcd < 10) begin hr10 = 0; hr = bcd; end
					else if(bcd < 20) begin hr10 = 1; hr = bcd - 10; end
					else begin hr10 = 2; hr = bcd - 20; end
				end
				if(!stop_enable_sec)begin
					case (hr)
						0:display = 7'b000_0001;
						1:display = 7'b100_1111;
						2:display = 7'b001_0010;
						3:display = 7'b000_0110;
						4:display = 7'b100_1100;
						5:display=  7'b010_0100;
						6:display = 7'b010_0000;
						7:display = 7'b000_1111;
						8:display = 7'b000_0000;
						9:display = 7'b000_0100;
						default: display = 7'b100_1111;
					endcase
					case (hr10)
						0:display10 = 7'b000_0001;
						1:display10 = 7'b100_1111;
						2:display10 = 7'b001_0010;
						default: display10 = 7'b100_1111;
					endcase
				end
			end
			else
				a = a + 1;
			if(stop_enable_sec)begin display =7'b000_0001; display10 = 7'b000_0001;end
		end
	end
endmodule 