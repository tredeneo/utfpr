/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author daniel
 */
import java.sql.*;
public class intro_banco_de_dados {
    private static Connection con;
    private static Statement stmt;
    private static ResultSet rs;
    public static String ultimo()
    {
        String aux;
        try {
            rs.last();
            aux = FormataString();
        } catch (SQLException sql1) {
            aux = sql1.getMessage();
        }
        return aux;
    }
    public static String anterior()
    {
        String aux;
        try {
            rs.previous();
            aux = FormataString();
        } catch (SQLException sql1) {
            aux = sql1.getMessage();
        }
        return aux;
    }
    public static String proximo()
    {

        String aux;
        try {
            rs.next();
            aux = FormataString();
        } catch (SQLException sql1) {
            aux = sql1.getMessage();
        }
        return aux;
    }
    public static void carregaBanco()
    {
        try {
            con = DriverManager.getConnection(
                "jdbc:mysql://localhost/universidade", "aula", "123");
            stmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
            rs = stmt.executeQuery("select id,dept_name,tot_cred, name from student");
        } catch (SQLException sql1) {
        }
    }
    public static String FormataString()
    {
        String aux;
        try {
            aux = " identificação:" + rs.getString("id")
                + "\n departamento:" + rs.getString("dept_name")
                + "\n credito: " + rs.getString("tot_cred")
                + "\n nome: " + rs.getString("name");
        } catch (SQLException sql1) {
            aux = sql1.getMessage();
        }
        return aux;
    }
    public static String inicio()
    {
        String aux;
        try {
            rs.first();
            aux = FormataString();
        } catch (SQLException sql1) {
            aux = sql1.getMessage();
        }
        return aux;
    }

    public static void main(String[] args) throws Exception
    {
        /* testes
        carregaBanco();
        System.out.println(proximo());
        System.out.println(proximo());
        System.out.println(anterior());
        System.out.println(ultimo());
        System.out.println(inicio());
        */
    }
}
