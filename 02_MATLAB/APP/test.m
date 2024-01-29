clear
myMatrix = randi([1, 100], 10, 3);
zmienna = randi([1,100],1)
name = ['matrix',num2str(zmienna)]
save(fullfile(fileparts(mfilename('fullpath')), ['matrix',name,'data.mat']), 'myMatrix');

% for i = 1:10
%     newRow = randi([1, 100], 1, 3);
%     myMatrix = [myMatrix; newRow];
%     save(fullfile(fileparts(mfilename('fullpath')), 'matrix_data.mat'), 'myMatrix');
% end