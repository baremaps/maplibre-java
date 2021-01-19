package com.baremaps.maplibre;

import java.nio.file.FileSystems;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

public class MapLibre {

    private static String OS = System.getProperty("os.name").toLowerCase();
    public static boolean IS_WINDOWS = OS.contains("win");
    public static boolean IS_MAC = OS.contains("mac");
    public static boolean IS_UNIX = OS.contains("nix") || OS.contains("nux") || OS.contains("aix");

    static {
        loadLibrary("maplibre-native");
    }

    public static void loadLibrary(String libraryName) {
        String libraryFile;
        if (IS_UNIX) {
            libraryFile = String.format("%s.so", libraryName);
        } else if (IS_MAC) {
            libraryFile = String.format("lib%s.dylib", libraryName);
        } else if (IS_WINDOWS) {
            libraryFile = String.format("%s.dll", libraryName);
        } else {
            throw new RuntimeException("Unsupported operating system");
        }
        String libraryPath = String.format("/native/%s", libraryFile);
        try (InputStream stream = MapLibre.class.getResourceAsStream(libraryPath)) {
            String[] parts = libraryFile.split("\\.");
            String prefix = String.format("%s-", parts[0]);
            String suffix = String.format(".%s", parts[1]);
            File tempFile = File.createTempFile(prefix, suffix);
            Files.copy(stream, tempFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
            System.load(tempFile.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public native byte[] render(int height, int width, double pixelRatio, double latitude, double longitude, double zoom);

    public static void main(String... args) throws Exception {
        byte[] buf = new MapLibre().render(500, 500, 4, 46.6189, 6.5743, 14);
        System.out.println(buf.length);
        Files.write(Paths.get("java.png"), buf);
    }

}