package com.example.myapplication;

import static android.view.View.VISIBLE;

import android.content.res.Configuration;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

public class SecondFragment extends Fragment {

    String[] desserts = {"ΒΑΦΛΑ", "ΜΠΑΝΟΦΙ", "ΤΙΡΑΜΙΣΟΥ"};
    String[] seafood = {"ΚΑΛΑΜΑΡΑΚΙΑ", "ΤΣΙΠΟΥΡΑ", "ΓΑΡΙΔΕΣ"};
    String[] meats = {"ΧΟΙΡΙΝΗ ΜΠΡΙΖΟΛΑ", "ΜΟΣΧΑΡΙΣΙΑ ΜΠΡΙΖΟΛΑ", "ΚΟΤΟΠΟΥΛΟ ΑΛΑ ΚΡΕΜ"};

    private View rootView;
    boolean skipnextselect;
    private String category_keyword;
    private int lastOrientation = Configuration.ORIENTATION_UNDEFINED;
    //private MainActivity.SharedSelectionViewModel viewModel;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.fragment2, container, false);

        if (getArguments() != null) {
            String keyword = getArguments().getString("keyword", null);
            if (keyword != null) {
                updateContentBasedOnSelection(keyword);
            }


        }
        lastOrientation = getResources().getConfiguration().orientation;
        if(lastOrientation==Configuration.ORIENTATION_PORTRAIT)
        {
            ChangeBackground(MainActivity.easter);
        }
        return rootView;
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        SetUpRadioGroupListener(view);
    }

    public void updateContentBasedOnSelection(String keyword) {
        if (rootView == null) return;

        RadioGroup recipe_selector = rootView.findViewById(R.id.recipe_select_secondary);
        recipe_selector.setVisibility(VISIBLE);
        RadioButton recipe1 = rootView.findViewById(R.id.recipe1);
        RadioButton recipe2 = rootView.findViewById(R.id.recipe2);
        RadioButton recipe3 = rootView.findViewById(R.id.recipe3);
        ImageView food_category = rootView.findViewById(R.id.FoodCategoryImage);
        food_category.setVisibility(VISIBLE);
        category_keyword = keyword;
        recipe_selector.clearCheck();
        switch (keyword) {
            case "desserts":
                recipe1.setText(desserts[0]);
                recipe2.setText(desserts[1]);
                recipe3.setText(desserts[2]);
                food_category.setImageResource(R.drawable.desserts_image);
                break;

            case "seafood":
                recipe1.setText(seafood[0]);
                recipe2.setText(seafood[1]);
                recipe3.setText(seafood[2]);
                food_category.setImageResource(R.drawable.seafood_image);
                break;

            case "meat":
                recipe1.setText(meats[0]);
                recipe2.setText(meats[1]);
                recipe3.setText(meats[2]);
                food_category.setImageResource(R.drawable.meat_image);
                break;
        }
    }

    private void SetUpRadioGroupListener(View view) {
        RadioGroup Recipe_Selector = view.findViewById(R.id.recipe_select_secondary);
        if (Recipe_Selector != null) {
            Recipe_Selector.setOnCheckedChangeListener((group1, checkedId) -> {
               // skipnextselect = true;

                int orientation = getResources().getConfiguration().orientation;
                RadioButton selectedButton = view.findViewById(checkedId);
                if (selectedButton != null) {
                    String food_keyword = selectedButton.getText().toString();
                    Log.d("SelectedKeyword", food_keyword);

                    if (orientation == Configuration.ORIENTATION_PORTRAIT) {

                            Recipe_Selector.setOnCheckedChangeListener(null);
                            Recipe_Selector.clearCheck();


                        ThirdFragment thirdFragment = new ThirdFragment();
                        Bundle args = new Bundle();
                        args.putString("keyword_from_second", food_keyword);
                        args.putString("category_keyword", category_keyword);
                        thirdFragment.setArguments(args);

                        requireActivity().getSupportFragmentManager()
                                .beginTransaction()
                                .replace(R.id.fragment_container, thirdFragment)
                                .addToBackStack(null)
                                .commit();
                    } else if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
                        Log.d("checkedID",String.valueOf(checkedId));

                        Fragment fragment = requireActivity().getSupportFragmentManager()
                                .findFragmentById(R.id.fragment3);
                        if (food_keyword != null && category_keyword != null) {
                            if (fragment instanceof ThirdFragment) {
                                ((ThirdFragment) fragment).setContent(food_keyword, category_keyword,true);
                            }
                        }
                    }
                }
            });
        }

    }

    public void ChangeBackground(boolean easter_trigger) {

        if(easter_trigger)
        {
            Drawable drawable = ContextCompat.getDrawable(requireContext(), R.drawable.space);
            rootView.setBackground(drawable);
        }
        else
        {
            Drawable drawable = ContextCompat.getDrawable(requireContext(), R.drawable.background_opacity);
            rootView.setBackground(drawable);

        }
    }

}

