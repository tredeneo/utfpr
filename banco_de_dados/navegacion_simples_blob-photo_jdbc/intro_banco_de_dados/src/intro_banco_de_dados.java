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
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.*;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

public class intro_banco_de_dados {
    private static Connection con;
    private static Statement stmt;
    private static ResultSet rs;
    private static File diretorio;
    public static void ultimo()
    {
        try {
            rs.last();
        } catch (SQLException ignored) {
        }
    }
    public static void anterior()
    {
        try {
            rs.previous();
        } catch (SQLException ignored) {
        }
    }
    public static void proximo()
    {
        try {
            rs.next();
        } catch (SQLException ignored) {
        }
    }
    public static void carrega_driver()
    {
        try{
            con = DriverManager.getConnection(
                "jdbc:mysql://localhost/universidade", "aula", "123");
        }catch(SQLException ignored){
        }
        
    }
    public static void carrega_banco()
    {
        try {
            stmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
            rs = stmt.executeQuery("select id,dept_name, name,photo from instructor");
        } catch (SQLException ignored) {
        }
    }
    public static String pega_string(String campo)
    {
        String aux;
        try {
            aux = rs.getString(campo);
        } catch (SQLException sql1) {
            aux = null;
        }
        return aux;
    }
    public static ImageIcon pega_icone()
    {   
        ImageIcon icone = new ImageIcon();
        InputStream input;
        try{
            java.sql.Blob blob = rs.getBlob("photo");
            input = blob.getBinaryStream();
            icone = new ImageIcon(ImageIO.read(input));
        }catch(IOException | SQLException ignored){
            
        }
        return icone;
    }
    public static void inicio()
    {
        try {
            rs.first();
        } catch (SQLException ignored) {
        }
    }

    public static void set_nomes_arquivos(){
        Path atual_relativo = Paths.get("");
        diretorio = new File(atual_relativo.toAbsolutePath().toString()+"/Imagens/");
    }
    public static void adiciona_fotos()
    {
        carrega_banco();
        try{
            PreparedStatement pstmt = con.prepareStatement("update instructor set photo = ? where id = ?");
            while(rs.next()){          
                try{
                    File arquivo = new File(diretorio+"/"+pega_string("id")+".png");
                    FileInputStream input = new FileInputStream(arquivo);
                    pstmt.setBinaryStream(1, input);
                    pstmt.setString(2, pega_string("id"));
                    pstmt.executeUpdate();
                }catch(FileNotFoundException ignored){}
                
            }
          
        }catch(SQLException ignored)
        {
            
        }
    }
    public static void adicionar_coluna(){
        try{
        stmt = con.createStatement();
        stmt.execute("alter table instructor add photo blob");
        }catch(SQLException ignored)
        {
            
        }
    }
    public static void main(String[] args) //throws Exception
    {        
        carrega_driver();
        adicionar_coluna();
        set_nomes_arquivos();
        adiciona_fotos();
    }
}
