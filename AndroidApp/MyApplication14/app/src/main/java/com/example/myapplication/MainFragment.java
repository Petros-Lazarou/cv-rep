package com.example.myapplication;

import android.content.res.Configuration;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

public class MainFragment extends Fragment {

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {



        return inflater.inflate(R.layout.fragment1, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        setupRadioGroupListener(view);
        int orientation = getResources().getConfiguration().orientation;
        Drawable bg1 = ContextCompat.getDrawable(
                requireContext(),
                MainActivity.easter ? R.drawable.space : R.drawable.background_opacity);
        if(orientation == Configuration.ORIENTATION_PORTRAIT)
        {
            view.setBackground(bg1);
        }
        FloatingActionButton easter = view.findViewById(R.id.easter);
        easter.setOnClickListener(v -> {
            MainActivity.easter = !MainActivity.easter;
            Toast.makeText(requireContext(),R.string.easter_secret,Toast.LENGTH_LONG).show();
            if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
                Drawable bg = ContextCompat.getDrawable(
                        requireContext(),
                        MainActivity.easter ? R.drawable.space : R.drawable.background_opacity);
                view.setBackground(bg);


                //view.setBackground(bg);

                Fragment f2 = requireActivity()
                        .getSupportFragmentManager()
                        .findFragmentById(R.id.fragment2);
                if (f2 instanceof SecondFragment) {
                    ((SecondFragment) f2).ChangeBackground(MainActivity.easter);
                }

                Fragment f3 = requireActivity()
                        .getSupportFragmentManager()
                        .findFragmentById(R.id.fragment3);
                if (f3 instanceof ThirdFragment) {
                    ((ThirdFragment) f3).ChangeBackground(MainActivity.easter);
                }


            } else if (orientation == Configuration.ORIENTATION_PORTRAIT) {
                Drawable bg = ContextCompat.getDrawable(
                        requireContext(),
                        MainActivity.easter ? R.drawable.space : R.drawable.background_opacity
                );
                view.setBackground(bg);

                Fragment current = requireActivity()
                        .getSupportFragmentManager()
                        .findFragmentById(R.id.fragment_container);


            }
        });
    }

    private void setupRadioGroupListener(View view) {
        RadioGroup group = view.findViewById(R.id.recipe_select);
        group.setOnCheckedChangeListener((g, checkedId) -> {
            int orientation = getResources().getConfiguration().orientation;
            String keyword = null;
            if (checkedId == R.id.desserts) keyword = "desserts";
            else if (checkedId == R.id.meat) keyword = "meat";
            else if (checkedId == R.id.seafood) keyword = "seafood";

            if (orientation == Configuration.ORIENTATION_PORTRAIT) {
                g.setOnCheckedChangeListener(null);
                g.clearCheck();

                SecondFragment sf = new SecondFragment();
                Bundle args = new Bundle();
                args.putString("keyword", keyword);
                sf.setArguments(args);

                requireActivity()
                        .getSupportFragmentManager()
                        .beginTransaction()
                        .replace(R.id.fragment_container, sf)
                        .addToBackStack(null)
                        .commit();

            } else {
                Fragment f = requireActivity()
                        .getSupportFragmentManager()
                        .findFragmentById(R.id.fragment2);

                if (keyword != null && f instanceof SecondFragment) {
                    ((SecondFragment) f).updateContentBasedOnSelection(keyword);
                }
                Fragment f3 = requireActivity().getSupportFragmentManager().findFragmentById(R.id.fragment3);
                if(f3 instanceof  ThirdFragment)
                {
                    ((ThirdFragment) f3).hideAllViews();
                }
            }
        });
    }
}
