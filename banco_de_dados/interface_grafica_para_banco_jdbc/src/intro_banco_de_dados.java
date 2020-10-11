/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 *
 * @author daniel
 */
import java.io.File;
/*
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
*/
import java.sql.*;
import java.util.ArrayList;

public class intro_banco_de_dados {
    private static Connection con;
    private static Statement stmt;
    public static ResultSet rs;
    private static File diretorio;
    
    public static ArrayList<String> pega_linhas(){
        var resultado = new ArrayList<String>();
        try{
           while(rs.next())
           {
               resultado.add(rs.getString(1));
           }
        }         
        catch(SQLException ignored){
        }
        return resultado;
    }
       
    public static ArrayList<String> nome_colunas(){
        int quantidade;
        var colunas = new ArrayList<String>();
        //String[] colunas = New String[];
        try{
            quantidade = rs.getMetaData().getColumnCount();
            //colunas = new String[10];
            for (int i=1;i<=quantidade;i++)
            {
                colunas.add(rs.getMetaData().getColumnName(i));
            } 
        }catch(SQLException ignored){
        }
         return colunas;
        
    }
    
    public static void carrega_driver(String banco,String database,String endereco,String usuario,String senha )
    {
        try{
            con = DriverManager.getConnection(
                "jdbc:"+banco+"://"+endereco+"/"+database, usuario, senha);
        }catch(SQLException ignored){
        }
        
    }
    public static void carrega_codigo(String codigo)
    {
        try {
            stmt = con.createStatement(ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY);
            rs = stmt.executeQuery(codigo);
        } catch (SQLException ignored) {
        }
    }
    public static ArrayList<String> pega_colunas()
    {
        var resultado = new ArrayList<String>();
        

	try {
            var quantidade = rs.getMetaData().getColumnCount();
            if(rs.next())
            {
                for (int i=1; i<= quantidade; i++)
                {
                    resultado.add(rs.getString(i));
                }
            }
        } catch (SQLException ignored) {
        }
        return resultado;
    }

    public static void main(String[] args) //throws Exception
    {        
    }
}
