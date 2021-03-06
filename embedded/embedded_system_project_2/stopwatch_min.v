module stopwatch_min (clk, reset, enable, bcd, display, display10, tc);
	parameter N=60, M=6;
	input clk, reset, enable;
	output [M-1:0] bcd;
	output [6:0] display, display10;
	output tc;
	reg [M-1:0] bcd;
	reg [6:0] display, display10;
	integer a,mr, mr10;
	
	assign tc = (bcd == N-1) & enable;

	always @(posedge clk or posedge reset) begin
		if (reset) begin
			bcd = 0;
			mr = 0;
			mr10 = 0;
			display = 7'b000_0001;
			display10 = 7'b000_0001;
		end
		else if(enable) begin
			if(a == 249999) begin
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
					case (mr)
						0:display = 7'b000_0001;
						1:display = 7'b100_1111;
						2:display = 7'b001_0010;
						3:display = 7'b000_0110;
						4:display = 7'b100_1100;
						5:display= 7'b010_0100;
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
			else
				a = a + 1;
		end
	end
endmodule 