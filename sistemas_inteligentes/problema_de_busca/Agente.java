package sistema;

import ambiente.*;
import problema.*;
//import problemaEnuncT02.*;
import comuns.*;
import static comuns.PontosCardeais.*;

/**
 *
 * @author tacla
 */
public class Agente implements PontosCardeais {
    /* referência ao ambiente para poder atuar no mesmo*/
    Model model;
    Problema prob; // formulacao do problema
    Estado estAtu; // guarda o estado atual (posição atual do agente)
    /* @todo T2: fazer uma sequencia de acoes a ser executada em deliberar
       e armazena-la no atributo plan[]
    */
    int plan[] = {N, N, N, N, L, L, L, L, L, L, L, L, N, N};
    double custo;
    static int ct = -1;
           
    public Agente(Model m) {
        this.model = m;
        prob = new Problema();
        
        //@todo T2: Aqui vc deve preencher a formulacao do problema 
        
        //@todo T2: crencas do agente a respeito do labirinto
       prob.criarLabirinto(9, 9);
       prob.crencaLabir.parede[0][0] = 1;
       prob.crencaLabir.parede[1][0] = 1;
       prob.crencaLabir.parede[0][1] = 1;
       prob.crencaLabir.parede[5][1] = 1;
       prob.crencaLabir.parede[6][1] = 1;
       prob.crencaLabir.parede[7][1] = 1;
       prob.crencaLabir.parede[8][1] = 1;
       prob.crencaLabir.parede[5][2] = 1;
       prob.crencaLabir.parede[8][2] = 1;
       prob.crencaLabir.parede[2][3] = 1;
       prob.crencaLabir.parede[3][3] = 1;
       prob.crencaLabir.parede[0][4] = 1;
       prob.crencaLabir.parede[2][4] = 1;
       prob.crencaLabir.parede[3][4] = 1;
       prob.crencaLabir.parede[6][4] = 1;
       prob.crencaLabir.parede[7][4] = 1;
       prob.crencaLabir.parede[0][5] = 1;
       prob.crencaLabir.parede[2][5] = 1;
       prob.crencaLabir.parede[3][5] = 1;
       prob.crencaLabir.parede[5][5] = 1;
       prob.crencaLabir.parede[6][5] = 1;
       prob.crencaLabir.parede[0][6] = 1;
       prob.crencaLabir.parede[0][7] = 1;
       prob.crencaLabir.parede[1][7] = 1;
       prob.crencaLabir.parede[3][7] = 1;
       prob.crencaLabir.parede[5][7] = 1;
       prob.crencaLabir.parede[6][7] = 1;
       prob.crencaLabir.parede[7][7] = 1;
       
        
        
        //@todo T2: crencas do agente: Estado inicial, objetivo e atual
        // utilizar atributos da classe Problema
        prob.defEstIni(8, 0);
        prob.defEstObj(2, 8);
        estAtu = new Estado(8, 0);
        
    }
    
    /**Escolhe qual ação (UMA E SOMENTE UMA) será executada em um ciclo de raciocínio
     * @return 1 enquanto o plano não acabar; -1 quando acabar
     */
    public int deliberar() {
        ct++;
        //@todo T2: executar o plano de acoes: SOMENTE UMA ACAO POR CHAMADA DESTE METODO
        // Ao final do plano, verifique se o agente atingiu o estado objetivo verificando
        // com o teste de objetivo
        estAtu = sensorPosicao();
        if( prob.testeObjetivo(estAtu) == true)
            return -1;
        
        //@todo T2: imprimir o que foi pedido
        System.out.println("Estado atual: " + estAtu.getString());
        
        System.out.print("Ações possiveis: {");
        int[] acoes = prob.acoesPossiveis(estAtu);
        for (int i = 0; i < 8; i++)
            if(acoes[i] != -1)
                System.out.print(acao[i]+" ");
        
        System.out.print("}\nct =" + (ct+1) + " de " + plan.length + " ");
        //System.out.printf("ct = %d de %d ", ct+1, plan.length);
        
        System.out.println("ação escolhida = " + acao[plan[ct]]);
        executarIr(plan[ct]);
        Estado novoEstado = prob.suc(estAtu, plan[ct]);
        custo += prob.obterCustoAcao(estAtu, plan[ct], novoEstado);
        System.out.println("custo acumulado:" + custo);
        estAtu = novoEstado;
        
        
        return 1;
    }
    
    /**Funciona como um driver ou um atuador: envia o comando para
     * agente físico ou simulado (no nosso caso, simulado)
     * @param direcao N NE S SE ...
     * @return 1 se ok ou -1 se falha
     */
    public int executarIr(int direcao) {
        model.ir(direcao);
        return 1; 
    }   
    
    // Sensor
    public Estado sensorPosicao() {
        int pos[];
        pos = model.lerPos();
        return new Estado(pos[0], pos[1]);
    }
}    

