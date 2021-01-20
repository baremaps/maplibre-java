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
    private static boolean LINUX = OS.contains("nix") || OS.contains("nux") || OS.contains("aix");
    private static boolean MACOS = OS.contains("mac");

    private static long loopPointer;

    static {
        String libraryName = "maplibre-native";
        String libraryFile;
        if (LINUX) {
            libraryFile = String.format("lib%s.so", libraryName);
        } else if (MACOS) {
            libraryFile = String.format("lib%s.dylib", libraryName);
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
            loopPointer = startRunLoop();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static native long startRunLoop();

    private long mapLibrePointer;

    public MapLibre() {
        this(256, 256, 1);
    }

    public MapLibre(double width, double height, double pixelRatio) {
        mapLibrePointer = createMapLibre(width, height, pixelRatio);
    }

    private native long createMapLibre(double width, double height, double pixelRatio);

    public native void loadUrlStyle(String url);

    public native void setPosition(double latitude, double longitude, int zoom);

    public native void setCenter(double latitude, double longitude);

    public native void setZoom(int zoom);

    public native byte[] render();

    public static void main(String... args) throws Exception {
        MapLibre map = new MapLibre(512, 512, 2);
        map.loadUrlStyle("https://tiles.baremaps.com/style.json");
        map.setPosition(46.6189, 6.5743, 14);
        byte[] buf = map.render();
        System.out.println(buf.length);
        Files.write(Paths.get("java.png"), buf);
    }

}