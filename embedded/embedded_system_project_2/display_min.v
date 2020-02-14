	module count_display_min (clk, reset, enable ,display, display10, tc,stop_enable_sec,stop_enable_min,stopwatch,add_min);
	parameter N=60, M=6;
	input clk, reset, enable;
	input stop_enable_min,stop_enable_sec,stopwatch,add_min;
	output [6:0] display, display10;
	output tc;
	reg [M-1:0] bcd,stop_bcd;
	reg [6:0] display, display10;
	integer a,mr, mr10, stop_a,stop_mr,stop_mr10,check,check_return;
	
	assign tc = (bcd == N-1) & enable;

	always @(posedge clk or posedge reset) begin
		if (reset) begin
			bcd = 0;
			mr = 0;
			mr10 = 0;
			display = 7'b000_0001;
			display10 = 7'b000_0001;
		end
		else if(add_min) begin 
		if(a == 49999999) begin
			a=0;
			if(bcd == N-1) begin bcd = 0; mr10 = 0; mr = 0; end
			else begin 
				bcd = bcd + 1;
				if(bcd <10) begin mr10 = 0; mr = bcd; end
				else if(bcd <20) begin mr10 = 1; mr = bcd-10; end
				else if(bcd <30) begin mr10 = 2; mr = bcd-20; end
				else if(bcd <40) begin mr10 = 3; mr = bcd-30; end
				else if(bcd <50) begin mr10 = 4; mr = bcd-40; end
				else begin mr10 = 5; mr = bcd-50; end
			end
			check=0;
			case (mr)
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
			case (mr10)
				0:display10 = 7'b000_0001;
				1:display10 = 7'b100_1111;
				2:display10 = 7'b001_0010;
				3:display10 = 7'b000_0110;
				4:display10 = 7'b100_1100;
				5:display10 = 7'b010_0100;
				default: display10 = 7'b100_1111;
			endcase
					 
		end
		else begin
			a= a+1;
		end
		end
		
		else if(stopwatch & (check==0) & (check_return==0))begin
				display = 7'b000_0001;
				display10 = 7'b000_0001;
				check=1;
		end
		else if(stopwatch & (check==0)&(check_return==1))begin
			case (stop_mr)
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
					case (stop_mr10)
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
		else if(enable | stop_enable_min) begin
			if(enable) begin
				if(a == 49999999) begin
					a=0;
					if(bcd == N-1) begin bcd = 0; mr10 = 0; mr = 0; end
					else begin 
						bcd = bcd + 1;
						if(bcd <10) begin mr10 = 0; mr = bcd; end
						else if(bcd <20) begin mr10 = 1; mr = bcd-10; end
						else if(bcd <30) begin mr10 = 2; mr = bcd-20; end
						else if(bcd <40) begin mr10 = 3; mr = bcd-30; end
						else if(bcd <50) begin mr10 = 4; mr = bcd-40; end
						else begin mr10 = 5; mr = bcd-50; end
					end
					if(!stopwatch) begin
						check=0;
						case (mr)
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
						case (mr10)
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
			end 
			
			if(stop_enable_min) begin	//stopwatch
				check_return=1;
				if(stop_a == 499999) begin
					stop_a=0;
					if(stop_bcd == N-1) begin stop_bcd = 0; stop_mr10 = 0; stop_mr = 0; end
					else begin 
						stop_bcd = stop_bcd + 1;
						if(stop_bcd <10) begin stop_mr10 = 0; stop_mr = stop_bcd; end
						else if(stop_bcd <20) begin stop_mr10 = 1; stop_mr = stop_bcd-10; end
						else if(stop_bcd <30) begin stop_mr10 = 2; stop_mr = stop_bcd-20; end
						else if(stop_bcd <40) begin stop_mr10 = 3; stop_mr = stop_bcd-30; end
						else if(stop_bcd <50) begin stop_mr10 = 4; stop_mr = stop_bcd-40; end
						else begin stop_mr10 = 5; stop_mr = stop_bcd-50; end
					end
	
					case (stop_mr)
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
					case (stop_mr10)
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