outDP(8,1);
for(int k=0;k<4;k++)outDP(4+k,(count_rt[2]>>k) & 0x01);
for(t=0;t<500;t++);
outDP(8,0);

outDP(9,1);
for(int k=0;k<4;k++)outDP(4+k,(count_rt[1]>>k) & 0x01);
for(t=0;t<500;t++);
outDP(9,0);

outDP(10,1);
for(int k=0;k<4;k++)outDP(4+k,(count_rt[0]>>k) & 0x01);
for(t=0;t<500;t++);
outDP(10,0);