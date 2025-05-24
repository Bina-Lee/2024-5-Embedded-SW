void offall();
void on(int v);
void off(int v);

void main(){
    for(int i=0;i<4;i++){
        offall();
        for(int j=0;j<i;j++){
            on(j);
        }
        for(int j=i;j<4;j++){
            on(j);
            delay();
            off(j);
        }
        for(int j=3;j>=i;j--){
            on(j);
            delay();
            off(j);
        }
    }
}