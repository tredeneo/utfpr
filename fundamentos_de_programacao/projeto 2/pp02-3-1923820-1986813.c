/*nome:daniel de viveiros inácio
  ra:1923820
  nome:kelvin james de souza martins
  ra:1986813*/
void mudaGanho (double* dados, unsigned long n_amostras, double ganho){
    int i;
    for(i=0;i<n_amostras;i++){
        dados[i]=dados[i]*ganho;
    }
}
//===========================================================================//
void ruidoPeriodico (double* dados, unsigned long n_amostras,unsigned short intervalo){//foi usada uma variável auxiliar para ficar alternando entre 1 e -1.
    int i,aux=0;
    for(i=0;i<n_amostras;i=i+intervalo-1){
        if(aux==0){
            dados[i]=1;
            aux=1;
        }
        else if(aux==1){
            dados[i]=-1;
            aux=0;
        }
    }
}
//==========================================================//
void removeRuido(double* dados, unsigned long n_amostras){//a lógica principal foi encontrar o menor número no intervalo,depois disso só restou 2 posições no vetor,assim usamos if e else para localizar a mediana.
    int i,k;
    double *mediana;//a mediana só podia ser cálculada com os valores originais,então criamos um vetor que armazene todas as medianas para depois substituirmos.
    mediana=(double*)malloc(n_amostras*sizeof(double));
    for(i=1;i<(n_amostras-1);i++){
        if(dados[i]<=dados[i+1]&&dados[i]<=dados[i-1]){
            if(dados[i+1]<dados[i-1])
                mediana[i-1]=dados[i+1];
            else
                mediana[i-1]=dados[i-1];
        }
        else if(dados[i+1]<=dados[i-1]&&dados[i+1]<=dados[i]){
            if(dados[i]<dados[i-1])
                mediana[i-1]=dados[i];
            else
                mediana[i-1]=dados[i-1];
        }
        else if(dados[i-1]<=dados[i]&&dados[i-1]<=dados[i+1]){
            if(dados[i]<dados[i+1])
                mediana[i-1]=dados[i];
            else
                mediana[i-1]=dados[i+1];
        }
    }
    for(k=1;k<(n_amostras-1);k++){
        dados[k]=mediana[k-1];
    }
}
