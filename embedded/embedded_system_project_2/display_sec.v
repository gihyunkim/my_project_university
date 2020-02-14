module count_display_sec(clk, reset, set_outside, set_inside, enable, display, display10, tc, stop_enable_sec, stopwatch_tc,stopwatch);
	parameter N=60, M=6;
	input clk, reset, enable, set_outside, set_inside,stop_enable_sec,stopwatch;
	output [6:0] display, display10;
	output tc,stopwatch_tc;
	reg [M-1:0] bcd,stop_bcd;
	reg [6:0] display, display10;
	integer a,sr, sr10,stop_a,stop_sr,stop_sr10,check,check_return;
	
	assign tc = (bcd == N-1) & enable;
	assign stopwatch_tc = (stop_bcd == N-1) & stop_enable_sec;
	
	always @(posedge clk or posedge reset) begin
		if (reset) begin
			bcd = 0;
			sr = 0;
			sr10 = 0;
			check=0;
			display = 7'b000_0001;
			display10 = 7'b000_0001;
		end
		else if(stopwatch & (check==0) &(check_return==0))begin
				display = 7'b000_0001;
				display10 = 7'b000_0001;
				check=1;
		end
		else if(stopwatch & (check==0)&(check_return==1))begin
			case (stop_sr)
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
					case (stop_sr10)
						0:display10 = 7'b000_0001;
						1:display10 = 7'b100_1111;
						2:display10 = 7'b001_0010;
						3:display10 = 7'b000_0110;
						4:display10 = 7'b100_1100;
						5:display10 = 7'b010_0100;
						default: display10 = 7'b100_1111;
					endcase
				check=1;
		end
		else if((check==1) & !stopwatch & !enable)begin
			display = 7'b000_0001;
			display10 = 7'b000_0001;
			check=0;
		end
		else if(enable) begin
			if(a == 49999999) begin
				a=0;
				if(bcd == N-1) begin bcd = 0; sr10 = 0; sr = 0; end
				else begin 
					bcd = bcd + 1;
					if(bcd <10) begin sr10 = 0; sr = bcd; end
					else if(bcd <20) begin sr10 = 1; sr = bcd-10; end
					else if(bcd <30) begin sr10 = 2; sr = bcd-20; end
					else if(bcd <40) begin sr10 = 3; sr = bcd-30; end
					else if(bcd <50) begin sr10 = 4; sr = bcd-40; end
					else begin sr10 = 5; sr = bcd-50; end
				end
				if(!stopwatch) begin
					case (sr)
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
					case (sr10)
						0:display10 = 7'b000_0001;
						1:display10 = 7'b100_1111;
						2:display10 = 7'b001_0010;
						3:display10 = 7'b000_0110;
						4:display10 = 7'b100_1100;
						5:display10 = 7'b010_0100;
						default: display10 = 7'b100_1111;
					endcase
				end 
			end
			else begin
				a= a+1;
			end
		
			if(stop_enable_sec) begin	//stopwatch
				check_return=1;
				if(stop_a == 499999) begin
					stop_a=0;
					if(stop_bcd == N-1) begin stop_bcd = 0; stop_sr10 = 0; stop_sr = 0; end
					else begin 
						stop_bcd = stop_bcd + 1;
						if(stop_bcd <10) begin stop_sr10 = 0; stop_sr = stop_bcd; end
						else if(stop_bcd <20) begin stop_sr10 = 1; stop_sr = stop_bcd-10; end
						else if(stop_bcd <30) begin stop_sr10 = 2; stop_sr = stop_bcd-20; end
						else if(stop_bcd <40) begin stop_sr10 = 3; stop_sr = stop_bcd-30; end
						else if(stop_bcd <50) begin stop_sr10 = 4; stop_sr = stop_bcd-40; end
						else begin stop_sr10 = 5; stop_sr = stop_bcd-50; end
					end
	
					case (stop_sr)
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
					case (stop_sr10)
						0:display10 = 7'b000_0001;
						1:display10 = 7'b100_1111;
						2:display10 = 7'b001_0010;
						3:display10 = 7'b000_0110;
						4:display10 = 7'b100_1100;
						5:display10 = 7'b010_0100;
						default: display10 = 7'b100_1111;
					endcase
				end else stop_a =stop_a + 1;	
			end
		end
	end
endmodule 