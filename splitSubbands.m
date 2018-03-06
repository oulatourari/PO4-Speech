%function that splits the given input_signal in subbands
% input_signal: the signal to be split
% fs: sample frequency of the input_signal
% subbands: a matrix with different subband-signals in each row
% synthesis: a column vector with all synthesis_filters
function [subbands, f0, f2] = splitSubbands(input_signal, fs)
%% QMF Design parameters
df = fs/10;
Astop = 60;
fstep = fs/800;
Niter = 100;
Flength1 = 64;
Flength2 = 32;
%Flength3 = 32;

%% Generate h0, h1, f0 and f1
% First tree stage filter
[h0,~,f0,~] = QMF_design(fs,df,Astop,fstep,Niter,Flength1);
% Second tree stage filter
[h2,~,f2,~] = QMF_design(fs/2,df/2,Astop,fstep/2,Niter,Flength2); 
% Third stage filter
%[h4,h5,f4,f5] = QMF_design(fs/4,df/4,Astop,fstep/4,Niter,Flength3); 

%% Analysis
[c0,c1] = analysis(input_signal,h0);
[s0,s1] = analysis(c0,h2);
[s2,s3] = analysis(c1,h2);
%[s4,s5] = analysis(s0,h4);
%[s6,s7] = analysis(s1,h4);
subbands = [s0;s1;s2;s3];
end