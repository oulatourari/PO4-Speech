% Computes 2 subband signals from an input
% Inputs: inputstream and h0 (impulse response)
% Outputs: 2 subband signals

function [c0,c1] = analysis(input,h0)

input_even = input(2:2:end);
input_odd = input(1:2:end);

h0_even = h0(2:2:end);
h0_odd = h0(1:2:end);

x0 = conv(input_even,h0_even,'same');
y0 = conv(input_odd,h0_odd,'same');

c0 = x0 + y0;
c1 = x0 - y0;