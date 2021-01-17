import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Paths;

public class MapLibre {

    static {
        System.loadLibrary("maplibre");
    }

    public native byte[] render(int height, int width, double pixelRatio, double latitude, double longitude, double zoom);

    public static void main(String... args) throws Exception {
        byte[] buf = new MapLibre().render(500, 500, 4, 46.6189, 6.5743, 14);

        System.out.println(buf.length);

        Files.write(Paths.get("java.png"), buf);

    }

}