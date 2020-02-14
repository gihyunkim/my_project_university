module watch_project (clk, reset, set_outside, set_inside, display_sec, display_sec10, display_min, display_min10, display_hour, display_hour10, state );
	input clk, reset, set_outside, set_inside;
	output [6:0] display_sec, display_sec10, display_min, display_min10, display_hour, display_hour10;
	output [5:0] state;
	wire en_sec, en_sec10, en_min, en_min10, en_hour, en_hour10,stop_enable_sec,stopwatch_tc,stopwatch,add_hour,add_min;
	
	count_display_sec #(60,6) u1 (clk, reset, set_outside, set_inside, en_sec, display_sec, display_sec10, tc_sec,stop_enable_sec, stopwatch_tc,stopwatch);
	count_display_min #(60,6) u2 (clk, reset, en_min, display_min, display_min10, tc_min,stop_enable_sec,stopwatch_tc,stopwatch,add_min);
	count_display_hour #(24,5) u3 (clk, reset, en_hour, display_hour, display_hour10,stop_enable_sec,stopwatch,add_hour);

	controller u6 (clk, reset, set_outside, set_inside, tc_sec, tc_min, en_sec, en_min, 
	en_hour, state, stop_enable_sec,stop_enable_min,stopwatch_tc,stopwatch,add_hour,add_min);

	
endmodule 