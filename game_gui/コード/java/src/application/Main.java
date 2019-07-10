package application;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("gameSet.fxml"));
        primaryStage.setTitle("巡りますGUI");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        /*
        // gui_main.pyの起動
        try {
            String CUI_DIR_PATH = System.getProperty("user.dir") + "\\..\\cui\\";
            System.out.println(CUI_DIR_PATH);
            Runtime runtime = Runtime.getRuntime();
            runtime.exec("python gui_main.py", null, new File(CUI_DIR_PATH));
        } catch (IOException e) {
            e.printStackTrace();
        }*/
    }


    public static void main(String[] args) {
        launch(args);
    }
}
