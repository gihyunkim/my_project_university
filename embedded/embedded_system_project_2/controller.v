module controller (clk, reset, b0, b1, tc_sec, tc_min, en_sec, en_min, en_hour, 
state,stop_enable_sec,stop_enable_min,stopwatch_tc,stopwatch,add_hour,add_min);

	input clk, reset, b0, b1, tc_sec, tc_min,stopwatch_tc;
	output en_sec, en_min, en_hour,stop_enable_sec,stop_enable_min,stopwatch,add_hour,add_min;
	output [5:0] state;
	reg [5:0] state;
	reg inc_min = 1, inc_hour = 1;
	integer a;
	parameter s0 = 1, s10 = 4, s11 = 6, s12 = 5, s20 = 8, s21 = 10, s22 = 9, s30 = 16, s31 = 18, s32 = 17;
	
	always @(posedge clk or posedge reset) begin
		if (reset) state <= s0;
		else begin
			if(a == 20000000) begin
				a=0;
				case (state)
					s0: if(!b0) state <= s10; 		//s0 : watch
						else if(!b1) state <= s30;
					
					s10: if(!b0) state <=s0; 		//s10 : set clock
						else if(!b1) state <= s11;
					s11: if(!b1) state <= s12;		//s11 : set hour
					s12: if(!b1) state <= s10;		//s12 : set min
				
					s30: if(!b0) state <= s31;		//s30 : stop watch
						else if(!b1) state <= s0;
					s31: if(!b0) state <= s32;		//s31 : start stop watch
					s32: if(!b0) state <= s30;		//s32 : stop stop watch
						else if(!b1) state <= s0;
				default : state <= s0;
			endcase
			end
			else
				a = a + 1;
		end
	end 
	
	assign en_sec = ((state == 4) | (state == 6) | (state == 5)) ? 0 : 1;
	assign en_min = (state == 5) ? 0 : tc_sec;
	assign en_hour = (state == 6) ? 0: tc_min;
	assign add_hour = ((state==6)&(!b0))? 1:0;
	assign add_min = ((state==5)&(!b0))? 1:0;
	assign alarm = ((state == 8) | (state == 10) | (state == 9)) ? 0 : 1;
	assign stopwatch = ((state==16)|(state==17)|(state==18)) ? 1: 0;
	assign stop_enable_sec = ((state==18)& (state!=17)) ? 1 : 0;
	assign stop_enable_min = stopwatch_tc;
endmodule 