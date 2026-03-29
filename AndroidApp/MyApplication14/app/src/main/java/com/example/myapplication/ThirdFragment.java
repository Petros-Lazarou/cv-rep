package com.example.myapplication;

import static android.view.View.INVISIBLE;
import static android.view.View.VISIBLE;

import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.TextPaint;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class ThirdFragment extends Fragment {

    private final List<metadata> desserts = new ArrayList<>();
    private final List<metadata> seafood = new ArrayList<>();
    private final List<metadata> meats = new ArrayList<>();
    private int lastOrientation = Configuration.ORIENTATION_UNDEFINED;
    String food_name;
    String category_food;
    View globalView;

    // Inner class for metadata
    private class metadata {
        String img_src;
        String ingredients;
        String recipe;
        String Dish_name;
        String category;
        String RecipeLink;
        String youtubeLink;

        public metadata(String dishName, String img_src, String ingredients, String recipe,
                        String category, String youtubeLink, String recipe_link) {
            this.Dish_name = dishName;
            this.img_src = img_src;
            this.ingredients = ingredients;
            this.recipe = recipe;
            this.category = category;
            this.youtubeLink = youtubeLink;
            this.RecipeLink = recipe_link;
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment3, container, false);
        globalView = view;
        lastOrientation = getResources().getConfiguration().orientation;

        if(lastOrientation == Configuration.ORIENTATION_PORTRAIT) {
            ChangeBackground(MainActivity.easter);
        }

        // Added referrerpolicy to iframes and fixed malformed URL parameters (? replaced with & where needed)
        desserts.add(new metadata("ΒΑΦΛΑ", "dessert1",
                readRawTextFile(R.raw.dessert1_ingredients),
                readRawTextFile(R.raw.dessert1_recipe),
                "ΓΛΥΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/XjgLQ9rpUxU?autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/basiki-syntagi-waffles/"));

        desserts.add(new metadata("ΜΠΑΝΟΦΙ", "dessert2",
                readRawTextFile(R.raw.dessert2_ingredients),
                readRawTextFile(R.raw.dessert2_recipe),
                "ΓΛΥΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/t5uSpoZZOuU?si=8IQkaGCss9ej2Pne&autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/mpanofi-banoffee/"));

        desserts.add(new metadata("ΤΙΡΑΜΙΣΟΥ", "dessert3",
                readRawTextFile(R.raw.dessert3_ingredients),
                readRawTextFile(R.raw.dessert3_recipe),
                "ΓΛΥΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/69FfHBrvT_4?si=lrYeEdVAPspSRFHu&autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/theiko-tiramisou-me-sokolata/"));

        meats.add(new metadata("ΧΟΙΡΙΝΗ ΜΠΡΙΖΟΛΑ", "meat1",
                readRawTextFile(R.raw.meat1_ingredients),
                readRawTextFile(R.raw.meat1_recipe),
                "ΚΡΕΑΣ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/T87cAOk_Qas?autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/choirines-mprizoles-sto-fourno-patates/"));

        meats.add(new metadata("ΜΟΣΧΑΡΙΣΙΑ ΜΠΡΙΖΟΛΑ", "meat2",
                readRawTextFile(R.raw.meat2_ingredients),
                readRawTextFile(R.raw.meat2_recipe),
                "ΚΡΕΑΣ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/4QlkF7rMfAs?si=C2qoG3g8c8rIXdCp&autoplay=1\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/mosxarisia-mprizola-stablisia-marinarismeni/"));

        meats.add(new metadata("ΚΟΤΟΠΟΥΛΟ ΑΛΑ ΚΡΕΜ", "meat3",
                readRawTextFile(R.raw.meat3_ingredients),
                readRawTextFile(R.raw.meat3_recipe),
                "ΚΡΕΑΣ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/r1XY_Tyb6N0?autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/kotopoulo-ala-krem-me-ruzi/"));

        seafood.add(new metadata("ΚΑΛΑΜΑΡΑΚΙΑ", "seafood1",
                readRawTextFile(R.raw.sea_food1_ingredients),
                readRawTextFile(R.raw.sea_food1_recipe),
                "ΨΑΡΙΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/NK1RRGaHi8w?si=g9xxKWUHVM7TUqOa&autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/kalamarakia-tiganita/"));

        seafood.add(new metadata("ΤΣΙΠΟΥΡΑ", "seafood2",
                readRawTextFile(R.raw.sea_food2_ingredients),
                readRawTextFile(R.raw.sea_food2_recipe),
                "ΨΑΡΙΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/iPXU20MM364?si=WbFJc2LuD4w9x1LY&autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/tsipoura-sto-fourno-apo-tin-argyro/"));

        seafood.add(new metadata("ΓΑΡΙΔΕΣ", "seafood3",
                readRawTextFile(R.raw.sea_food3_ingredients),
                readRawTextFile(R.raw.sea_food3_recipe),
                "ΨΑΡΙΚΑ", "<html><body><iframe referrerpolicy=\"strict-origin-when-cross-origin\" width=\"100%\" height=\"100%\" src=\"https://www.youtube.com/embed/79nqfKPW8TY?autoplay=1&rel=0&showinfo=0\" frameborder=\"0\" allowfullscreen></iframe></body></html>", "https://www.argiro.gr/recipe/garides-tiganites/"));

        return view;
    }

    private String readRawTextFile(int rawResID) {
        InputStream inputStream = getResources().openRawResource(rawResID);
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder sb = new StringBuilder();
        String line;
        try {
            while ((line = reader.readLine()) != null) {
                sb.append(line).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return sb.toString().trim();
    }

    public void setContent(String food_keyword, String Category_keyword, boolean visibility) {

        ImageView image = globalView.findViewById(R.id.recipeImage);
        TextView ingredients = globalView.findViewById(R.id.ingredients);
        TextView process = globalView.findViewById(R.id.process);
        TextView hyper_link = globalView.findViewById(R.id.hyper_text);
        WebView youtubeWebView = globalView.findViewById(R.id.youtubeView);
        TextView dish_name = globalView.findViewById(R.id.dish_name);
        TextView dish_category = globalView.findViewById(R.id.dish_category);

        WebSettings webSettings = youtubeWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setMediaPlaybackRequiresUserGesture(false); // Allows autoplay to work
        webSettings.setDomStorageEnabled(true); // Fix for Error 152 -4 (allows local storage for YouTube tracking scripts)

        youtubeWebView.setWebViewClient(new WebViewClient());
        youtubeWebView.setWebChromeClient(new android.webkit.WebChromeClient());

        metadata selectedDish = null;

        // Refactored to find the correct dish without repeating UI code
        if (Category_keyword.equals("desserts")) {
            for (metadata m : desserts) {
                if (food_keyword.equals(m.Dish_name)) {
                    selectedDish = m;
                    break;
                }
            }
        } else if (Category_keyword.equals("seafood")) {
            for (metadata m : seafood) {
                if (food_keyword.equals(m.Dish_name)) {
                    selectedDish = m;
                    break;
                }
            }
        } else if (Category_keyword.equals("meat")) {
            for (metadata m : meats) {
                if (food_keyword.equals(m.Dish_name)) {
                    selectedDish = m;
                    break;
                }
            }
        }

        // Apply UI updates once if a dish was found
        if (selectedDish != null) {
            int resID = getResources().getIdentifier(selectedDish.img_src, "drawable", requireContext().getPackageName());
            image.setImageResource(resID);
            ingredients.setText(selectedDish.ingredients);
            process.setText(selectedDish.recipe);
            setRecipeLink(hyper_link, selectedDish.RecipeLink);

            // The magic fix for Error 153 and 152 -4 combined
            youtubeWebView.loadDataWithBaseURL("https://www.youtube-nocookie.com", selectedDish.youtubeLink, "text/html", "utf-8", null);

            dish_name.setText(selectedDish.Dish_name);
            dish_category.setText(selectedDish.category);
        }

        if (visibility) {
            image.setVisibility(VISIBLE);
            ingredients.setVisibility(VISIBLE);
            process.setVisibility(VISIBLE);
            hyper_link.setVisibility(VISIBLE);
            dish_name.setVisibility(VISIBLE);
            dish_category.setVisibility(VISIBLE);
            youtubeWebView.setVisibility(VISIBLE);
        }
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        if (getArguments() != null) {
            int orientation = getResources().getConfiguration().orientation;
            if(orientation == Configuration.ORIENTATION_PORTRAIT) {
                food_name = getArguments().getString("keyword_from_second", null);
                category_food = getArguments().getString("category_keyword", null);
                Log.d("name_food", food_name);
                Log.d("category_food", category_food);
                setContent(food_name, category_food, true);
            }
        }
    }

    private void setRecipeLink(TextView textView, String url) {
        SpannableString hyper_text = new SpannableString(getString(R.string.hyperlink));
        ClickableSpan click_to_link = new ClickableSpan() {
            @Override
            public void onClick(@NonNull View widget) {
                Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
                widget.getContext().startActivity(intent);
            }

            @Override
            public void updateDrawState(TextPaint ds) {
                super.updateDrawState(ds);
                ds.setColor(Color.RED);
                ds.setUnderlineText(true);
            }
        };
        hyper_text.setSpan(click_to_link, 0, hyper_text.length(), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        textView.setText(hyper_text);
        textView.setMovementMethod(LinkMovementMethod.getInstance());
    }

    public void ChangeBackground(boolean easter_trigger) {
        if(easter_trigger) {
            Drawable drawable = ContextCompat.getDrawable(requireContext(), R.drawable.space);
            globalView.setBackground(drawable);
        } else {
            Drawable drawable = ContextCompat.getDrawable(requireContext(), R.drawable.background_opacity);
            globalView.setBackground(drawable);
        }
    }

    public void hideAllViews() {
        View root = getView();
        if (root == null) return;

        root.findViewById(R.id.recipeImage).setVisibility(INVISIBLE);
        root.findViewById(R.id.ingredients).setVisibility(INVISIBLE);
        root.findViewById(R.id.process).setVisibility(INVISIBLE);
        root.findViewById(R.id.hyper_text).setVisibility(INVISIBLE);
        root.findViewById(R.id.dish_name).setVisibility(INVISIBLE);
        root.findViewById(R.id.dish_category).setVisibility(INVISIBLE);
        root.findViewById(R.id.youtubeView).setVisibility(INVISIBLE);
    }
}